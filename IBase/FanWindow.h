#pragma once
#include "WinRoaming/Window.h"
#include "Data.hpp"
#include <vector>
namespace IBase
{
	namespace IWindows
	{
		using namespace window;
		using namespace Data;
		class FanWindow : public Window
		{
		public:
			using FanData = VData<6>;
			using BandData = VData<4>;
			using AlbumData = VData<4>;
			using SongData = VData<3>;
			using ConcertData = VData<4>;
		public:
			FanWindow(string name = "Fan", string _parent = "Login") :Window(name, _parent) {}
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		private:
			FanData fandata;
			std::vector<BandData> bandlikes;
			std::vector<AlbumData> albumlikes;
			std::vector<SongData> songlikes;
			std::vector<ConcertData> concertattends;
			
		private:
			void init(string account, string password);
			void initFanData(string account, string passwords);
			void initBandData();
			void initAlbumData();
			void initSongData();
			void initConcertData();

			void insertLikeBand(string name);
			void insertLikeAlbum(string name);
			void insertLikeSong(string name);
			void insertLikeConcert(string name);

			tuple<vector<IBase::IWindows::FanWindow::ConcertData>,
				vector<IBase::IWindows::FanWindow::AlbumData>,
				vector<IBase::IWindows::FanWindow::SongData>,
				vector<IBase::IWindows::FanWindow::BandData>> 
				searchByName(string s);
		};

	}
}