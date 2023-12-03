#pragma once
#include "WinRoaming/Window.h"
namespace IBase
{
	namespace IWindows
	{
		using namespace window;
		class RegisterWindow : public Window
		{
		public:
			RegisterWindow(string name = "Register", string _parent = "Login") :Window(name, _parent) {}
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		private:
			string registerUser();
			bool checkUserName();
			bool checkPass();
			string account;
			string password;
			string username;
		};

	}
}