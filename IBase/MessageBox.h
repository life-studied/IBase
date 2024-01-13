#pragma once
#include <string>
#include "imgui.h"

namespace IBase
{
	namespace WidgetTools
	{
		using std::string;
		using namespace ImGui;
		class IMMessageBox
		{
		public:
			IMMessageBox(string s)
			{
				bool isOpen = true;
				Begin(u8"��ʾ", &isOpen);
				Text(s.c_str());
				isClicked = Button(u8"ȷ��");
				End();
			}
		private:
			bool isClicked = false;
		public:
			bool isClick() { return isClicked; };
		};
	}
}