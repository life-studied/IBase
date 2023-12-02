#pragma once
#include "WinRoaming/Window.h"
namespace IBase
{
	namespace IWindows
	{
		using namespace window;
		class LoginWindow : public Window
		{
		public:
			LoginWindow(string name = "Login", string _parent = "") :Window(name, _parent) {}
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		};
	}
}