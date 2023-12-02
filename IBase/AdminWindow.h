#pragma once
#include "WinRoaming/Window.h"
namespace IBase
{
	namespace IWindows
	{
		using namespace window;
		class AdminWindow : public Window
		{
		public:
			AdminWindow(string name = "Admin", string _parent = "Login") :Window(name, _parent) {}
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		};

	}
}