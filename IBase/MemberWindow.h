#pragma once
#include "WinRoaming/Window.h"
#include "Data.hpp"
namespace IBase
{
	namespace IWindows
	{
		using namespace window;
		using namespace Data;
		class MemberWindow : public Window
		{
		public:
			using MemberData = VData<7>;
			using BandData = VData<5>;
			using NewData = VData<3>;	// time activity intro
			using AlbumData = VData<5>;
			using FanData = VData<5>;
			using ConcertData = VData<3>;
			using SongData = VData<2>;
		public:
			MemberWindow(string name = "Member", string _parent = "Login") :Window(name, _parent) {}
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		private:
			bool InBand = true;
			MemberData memberdata;
			BandData banddata;
			vector<MemberData> members;
			vector<NewData> news;
			vector<AlbumData> albums;
			vector<FanData> fans;
			vector<ConcertData> concerts;
			vector<SongData> songs;

			// 初始化成员信息
			void init(string account, string password);
			void initMember(string account,string password);
			void initAllMembers();
			void initBand();
			void initNews();
			void initAlbums();
			void initFans();
			void initConcerts();
			void initSongs();

			void quitBand();

			void clearAll();

			void backBand();
			bool attendBand();

			void updateSelfInfo();

			void addAlbum(AlbumData &data);
			void addSong(SongData &data);
			void addConcert(ConcertData &data);

			vector<FanData> searchFansBySong(string name);
			vector<FanData> searchFansByConcert(string name);
			vector<FanData> searchFansByAlbum(string name);

			void deleteSongByName(string name);
			void deleteConcertByName(string name);
			void deleteAlbumByName(string name);
		};

	}
}