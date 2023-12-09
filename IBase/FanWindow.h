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
			FanWindow(string name = "Fan", string _parent = "Login") :Window(name, _parent) {}
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		private:
			FanData fandata;
			std::vector<BandData> bandlikes;
			std::vector<AlbumData> albumlikes;
			std::vector<SongData> songlikes;
			std::vector<ConcertData> concertattends;
		};

	}
}