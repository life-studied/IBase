#include "LoginWindow.h"
#include "imgui.h"
std::string IBase::IWindows::LoginWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	using namespace ImGui;
	static char AccountBox[50] = u8"输入你的账号";
	static char PasswordBox[50] = u8"输入你的密码";
	bool isOpen = true;
	Begin("Login",&isOpen);
	InputText(u8"账号",AccountBox,IM_ARRAYSIZE(AccountBox));
	InputText(u8"密码",PasswordBox,IM_ARRAYSIZE(PasswordBox));
	account = AccountBox;
	password = PasswordBox;
	bool click = Button(u8"登录");
	End();
	if (!isOpen)	return {};
	if (click)	return "Admin";
	return getName();
}
