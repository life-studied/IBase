#pragma once
#include <vector>
#include <array>
#include "imgui.h"
#include "Data.hpp"
namespace IBase
{
	namespace helperWindows
	{
		using namespace Data;
		using namespace ImGui;

		template<size_t nameIndex, size_t N>
		class ListWindow
		{
		public:
			ListWindow(const string& _title, const vector<VData<N>>& _datas) : title(_title), datas(_datas) {}
			void showList()
			{
				BeginListBox(title.c_str());
				for (auto& i : datas)
					if (Selectable(i.strs[nameIndex].c_str(), true))
					{
						isChildWindowShow = true;
						temp = i;
					}
				EndListBox();
			}
			template <size_t label_N>
			void showWindow(const string (&labels)[label_N], const array<size_t,label_N> indexs)
			{
				if (isChildWindowShow)
				{
					Begin(title.c_str(),&isChildWindowShow);
					for (size_t i = 0; i < label_N; i++)
					{
						Text(labels[i].c_str()); SameLine(); Text(temp.strs[indexs[i]].c_str());
					}
					End();
				}
			}
		private:
			bool isChildWindowShow = false;
			VData<N> temp;
			string title;
			vector<VData<N>> datas;
		};
	}
}