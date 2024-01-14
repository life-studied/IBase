#include "MessageBox.h"

IBase::WidgetTools::IMMessageBox::IMMessageBox(string s)
{
	bool isOpen = true;
	Begin(u8"提示", &isOpen);
	Text(s.c_str());
	isClicked = Button(u8"确定");
	End();
}

bool IBase::WidgetTools::IMMessageBox::isClick()
{
	return isClicked;
}
