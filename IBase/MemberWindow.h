#pragma once
#include "WinRoaming/Window.h"
namespace IBase
{
	namespace IWindows
	{
		using namespace window;
		class MemberWindow : public Window
		{
		public:
			MemberWindow(string name = "Member", string _parent = "Login") :Window(name, _parent) {}
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		};

	}
}