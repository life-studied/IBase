#pragma once
#include "MysqlConnPool.h"
#include <vector>
#include <string>
namespace DBConn
{
	using std::vector;
	struct Table
	{
		vector<string> titles;
		vector<vector<string>> content;
	};

	struct Number
	{
		string name;
		string data;
	};

	
	namespace MysqlOP
	{

		inline const char root[] = "Configs/dbConfig/rootConfig.json";
		inline const char member[] = "Configs/dbConfig/memberConfig.json";
		inline const char fan[] = "Configs/dbConfig/fanConfig.json";

		template<const char* username>
		class MysqlOP
		{
		public:
			// query result is a table
			static Table query(string sql)
			{
				Table table;
				auto& instance = Singleton<MysqlConnPool<username>>::getInstance();
				auto conn = instance.getConntion();
				conn->query(sql);
				auto colNum = conn->colNum();
				for (int i = 0; i < colNum; i++)
					table.titles.push_back(conn->title(i));
				while (conn->next())
				{
					vector<string> row;
					for (int i = 0; i < colNum; i++)
						row.push_back(conn->value(i));
					table.content.push_back(row);
				}
				return table;
			}

			// query result is a number
			static Number countNumber(string sql)
			{
				Number n;
				auto& instance = Singleton<MysqlConnPool<username>>::getInstance();
				auto conn = instance.getConntion();
				conn->query(sql);
				n.name = conn->title(0);
				if (conn->next())
					n.data = conn->value(0);
				return n;
			}


		};
	}
}

