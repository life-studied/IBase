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
			IMMessageBox(string s);
		private:
			bool isClicked = false;
		public:
			bool isClick();
		};
	}
}