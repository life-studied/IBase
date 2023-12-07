﻿#pragma once
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <exception>
#include "MysqlConn.h"
#include "WinRoaming/Singleton.hpp"
namespace DBConn
{
	using std::queue;
	using std::shared_ptr;
	using std::mutex;
	using std::condition_variable;

	template <const char* username>
	class MysqlConnPool
	{
	public:
		MysqlConnPool()
		{
			if (!config.parseJsonFile(username))
			{
				return;
			}

			for (int i = 0; i < config.minSize; i++)
			{
				addConn();
			}

			std::thread producer([this]()
				{
					while (true)
					{
						std::unique_lock<mutex> lock(mtx);
						auto awake_condition = [this]() {return pool.size() < config.minSize; };
						if (!awake_condition())
						{
							cv.wait(lock, awake_condition);
						}
						addConn();
						cv.notify_all();
					}
				}
			);
			std::thread recycler([this]()
				{
					while (true)
					{
						auto awake_condition = [this]() {return pool.size() > config.maxSize; };
						while (!awake_condition()) std::this_thread::yield();
						std::unique_lock<mutex> lock(mtx);
						auto frontConn = pool.front();
						if (frontConn->getAliveTime() > config.maxIdleTime)
						{
							pool.pop();
						}
					}
				}
			);

			producer.detach();
			recycler.detach();
		}

		~MysqlConnPool()
		{
			isOver = true;
		}
		shared_ptr<MysqlConn> getConntion()
		{
			std::unique_lock<mutex> lock(mtx);
			while (pool.empty())
				if (std::cv_status::timeout == cv.wait_for(lock, std::chrono::milliseconds(config.timeOut)))
					if (pool.empty())
						continue;

			auto conn = pool.front();
			pool.pop();
			cv.notify_all();
			return conn;
		}
	private:
		void addConn()
		{
			std::shared_ptr<MysqlConn> conn(new MysqlConn,
				[this](MysqlConn* m) {
					if (isOver)
						delete m;
					else
					{
						auto conn = shared_ptr<MysqlConn>(m);
						conn->refreshAliveTime();
						std::lock_guard<mutex> lock(mtx);
						pool.push(conn);
						cv.notify_all();
					}
				}
			);
			if (!conn->connect(config))
				throw std::invalid_argument{u8"连接失败，请检查参数设置是否正确"};
			conn->refreshAliveTime();
			pool.push(conn);
		}
	private:
		MysqlConfig::MysqlConfig config;
		

		queue<shared_ptr<MysqlConn>> pool;
		bool isOver = false;
		mutex mtx;
		condition_variable cv;
	};
}

