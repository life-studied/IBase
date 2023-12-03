#include "LoginWindow.h"
#include "imgui.h"
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
	static char AccountBox[50] = u8"输入你的账号";
	static char PasswordBox[50] = u8"输入你的密码";
	bool isOpen = true;
	Begin("Login", &isOpen);
	InputText(u8"账号", AccountBox, IM_ARRAYSIZE(AccountBox));
	InputText(u8"密码", PasswordBox, IM_ARRAYSIZE(PasswordBox));
	account = AccountBox;
	password = PasswordBox;
	bool click = Button(u8"登录");
	bool click_regis = Button(u8"注册");

	End();
	if (!isOpen)	return {};
	if (click)
	{
		auto level = checkPass();
		return levelMap[level];
	}
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
	string safenumlist = "1234567890";
	if (password.find_first_not_of(safenumlist) != string::npos)
		return false;
	return true;
}
