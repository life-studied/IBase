#include "MessageBox.h"

IBase::WidgetTools::IMMessageBox::IMMessageBox(string s)
{
	bool isOpen = true;
	Begin(u8"��ʾ", &isOpen);
	Text(s.c_str());
	isClicked = Button(u8"ȷ��");
	End();
}

bool IBase::WidgetTools::IMMessageBox::isClick()
{
	return isClicked;
}
