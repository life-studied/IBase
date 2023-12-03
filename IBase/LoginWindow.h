#pragma once
#include "WinRoaming/Window.h"
namespace IBase
{
	namespace IWindows
	{
		using namespace window;

		enum class userLevel
		{
			None,
			Admin,
			Member,
			Fans
		};

		class LoginWindow : public Window
		{
		public:
			LoginWindow(string name = "Login", string _parent = "");
			virtual string drawNext(unordered_map<string, Window*>& windowlist) override;
		private:
			userLevel checkPass();
			bool safeCheck();
			string account;
			string password;
			unordered_map<userLevel, string> levelMap;
		};
		
	}
}