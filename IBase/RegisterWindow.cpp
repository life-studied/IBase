#include "RegisterWindow.h"
#include "imgui.h"
using namespace std;
using namespace ImGui;
string IBase::IWindows::RegisterWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	static char UsernameBox[50] = u8"输入你的用户名";
	static char PasswordBox[50] = u8"输入你的密码";
	bool isOpen = true;
	Begin("Register", &isOpen);
	InputText(u8"用户名", UsernameBox, IM_ARRAYSIZE(UsernameBox));
	InputText(u8"密码", PasswordBox, IM_ARRAYSIZE(PasswordBox));
	username = UsernameBox;
	password = PasswordBox;

	bool click = Button(u8"注册");
	static string regist_fail_show{u8"注册"};
	if (click) regist_fail_show =  registerUser();
	
	if (!regist_fail_show.empty()) Text(regist_fail_show.c_str());
	else { regist_fail_show = u8"注册"; return "RegisterSuccess"; }
	End();
	if (!isOpen) { regist_fail_show = u8"注册"; return parent; }
	
	return getName();
}

string IBase::IWindows::RegisterWindow::registerUser()
{
	size_t min_length = 6;
	if (username.size() < min_length) return { u8"用户名低于" + to_string(min_length) + "位" };
	if (password.size() < min_length) return { u8"密码低于" + to_string(min_length) + "位" };
	if (!checkUserName())	return { u8"用户名已存在" };
	if (!checkPass())	return { u8"密码存在特殊字符或空格" };
	
	// 生成随机ID并检查唯一性
	while(true)
	{ }
	// 注册用户

	return {};
}

bool IBase::IWindows::RegisterWindow::checkUserName()
{
	return false;
}

bool IBase::IWindows::RegisterWindow::checkPass()
{
	return false;
}
