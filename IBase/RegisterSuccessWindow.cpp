#include "RegisterSuccessWindow.h"
#include "imgui.h"
using namespace std;
using namespace ImGui;
string IBase::IWindows::RegisterSuccessWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	bool isOpen = true;
	Begin("Register Success", &isOpen);
	bool click = Button(u8"注册成功");
	End();
	if (!isOpen) return parent;
	if (click)	return parent;
	return getName();
}
