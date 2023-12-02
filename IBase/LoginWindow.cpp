#include "LoginWindow.h"
#include "imgui.h"
std::string IBase::IWindows::LoginWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	using namespace ImGui;
	bool isOpen = true;
	Begin("Login",&isOpen);
	Text(u8"账号");
	Text(u8"密码");
	End();
	if (!isOpen)	return {};
	return getName();
}
