#pragma once
#include "WinRoaming/Window.h"
namespace IBase
{
	namespace IWindows
	{
		using namespace window;
		class RegisterSuccessWindow : public Window
		{
		public:
			RegisterSuccessWindow(string name = "RegisterSuccess", string _parent = "Login") :Window(name, _parent) {}
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		private:
		};

	}
}