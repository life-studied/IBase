#include "MemberWindow.h"
#include "imgui.h"
using namespace std;
string IBase::IWindows::MemberWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	using namespace ImGui;
	bool isOpen = true;
	Begin("Member", &isOpen);

	End();
	if (!isOpen)return parent;
	return getName();
}
