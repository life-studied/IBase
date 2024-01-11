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
			void init(string account, string password);
			void initMember(string account,string password);
			void initAllMembers();
			void initBand();
			void initNews();
			void initAlbums();
			void initFans();
			void initConcerts();
			void quitBand();
		};

	}
}