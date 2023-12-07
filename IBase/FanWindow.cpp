#include "FanWindow.h"
#include "imgui.h"
using namespace std;
string IBase::IWindows::FanWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	using namespace ImGui;
	bool isOpen = true;
	Begin("Fan", &isOpen);

	End();
	if (!isOpen)return parent;
	return getName();
}
