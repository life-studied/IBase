#include "LoginWindow.h"
#include "imgui.h"
#include "TextureLoading.hpp"
#include "MysqlOP.h"
#define ADMIN "Admin"
#define MEMBER "Member"
#define FANS "Fans"
using namespace IBase::IWindows;
using namespace DBConn::MysqlOP;
IBase::IWindows::LoginWindow::LoginWindow(string name, string _parent) :Window(name, _parent)
{
	levelMap[userLevel::None] = getName();
	levelMap[userLevel::Admin] = ADMIN;
	levelMap[userLevel::Member] = MEMBER;
	levelMap[userLevel::Fans] = FANS;
}
std::string IBase::IWindows::LoginWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	using namespace ImGui;
	static char AccountBox[25] = u8"输入你的账号";
	static char PasswordBox[25] = u8"输入你的密码";
	bool isOpen = true;

	Begin("Login", &isOpen);
	auto size = GetWindowSize();
	auto length = size.x;
	auto width = size.y;

	// Load Image
	static int my_image_width = 0;
	static int my_image_height = 0;
	static GLuint my_image_texture = 0;
	static bool ret = LoadTextureFromFile("./circle-IBase.png", &my_image_texture, &my_image_width, &my_image_height);
	if (ret) 
	{ 
		SetCursorPosX(width / 2);
		SetCursorPosY(length / 10);
		Image((void*)(intptr_t)my_image_texture, ImVec2(200, 100));
	}

	// InputTexts
	SetCursorPosY(width/2);
	InputText(u8"账号", AccountBox, IM_ARRAYSIZE(AccountBox));
	InputText(u8"密码", PasswordBox, IM_ARRAYSIZE(PasswordBox));
	account = AccountBox;
	password = PasswordBox;

	// buttons
	SetCursorPosX(width / 10 * 8);
	bool click = Button(u8"登录"); SameLine();
	bool click_regis = Button(u8"注册");

	// show error label if login error
	static string label = "";
	if (label != "")
		Text(label.c_str());

	End();
	// close the window
	if (!isOpen)	return {};
	
	// check password and set label if wrong
	if (click)
	{
		auto level = checkPass();
		if (level == userLevel::None)
			label = u8"账号或密码错误";
		else
			label = "";
		return levelMap[level];
	}
	
	// go to register window
	if (click_regis)	return "Register";
	return getName();
}

userLevel IBase::IWindows::LoginWindow::checkPass()
{
	if (!safeCheck())
		return userLevel::None;
	auto sql = string("SELECT permission FROM Account WHERE account=") + account + " AND password='" + password + "'";

	auto Data = MysqlOP::countNumber(sql);
	if (Data.data.empty())
		return userLevel::None;
	else if (Data.data == ADMIN)
		return userLevel::Admin;
	else if (Data.data == MEMBER)
		return userLevel::Member;
	else if (Data.data == FANS)
		return userLevel::Fans;
	else
		return userLevel::None;
}

bool IBase::IWindows::LoginWindow::safeCheck()
{
	string unsafelist = " =";
	if (account.find_first_of(unsafelist) != string::npos)
		return false;
	if (password.find_first_of(unsafelist) != string::npos)
		return false;
	static string safenumlist = []() {
		string temp = "1234567890";
		for (auto i = 'a'; i <= 'z'; i++)
			temp += i;
		return temp;
	}();
	if (password.find_first_not_of(safenumlist) != string::npos)
		return false;
	return true;
}


