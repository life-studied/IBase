#include "AdminWindow.h"
#include "imgui.h"
std::string IBase::IWindows::AdminWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	using namespace ImGui;
	bool isOpen = true;
	Begin("Admin", &isOpen);
	auto isQuit = Button(u8"退出");
	End();
	if (!isOpen)return parent;
	if (isQuit)	return parent;
	return getName();
}
