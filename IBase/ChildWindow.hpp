#pragma once
#include <optional>
#include "imgui.h"
#include "Data.hpp"
namespace IBase
{
	namespace WidgetTools
	{
		using std::optional;
		using namespace ImGui;
		using namespace Data;
		template <size_t v_num>
		class ChildWindow
		{
		private:
			vector<VData<v_num>>* data;
			VData<v_num> selectedData;
			string name;
			bool windowShow = false;
			vector<string> labels;
		public:
			ChildWindow() = default;
			ChildWindow(vector<VData<v_num>>* _data) : data(_data) {}
			ChildWindow(vector<VData<v_num>>* _data, string _window_name, vector<string> _labels) : data(_data), name(_window_name), labels(_labels) {}
		public:
			void setName(string _name) { name = _name; }
			void setLabels(vector<string> _labels) { labels = _labels; }
			void setData(vector < VData<v_num>>* _data) { data = _data; }
			auto selected_str_by_index(size_t i)
			{
				return selectedData.strs[i];
			}

			void showList(size_t idx = 0)
			{
				BeginListBox(name.c_str());
				for (auto& i : *data)
					if (Selectable(i.strs[idx].c_str(), true))
					{
						windowShow = true;
						selectedData = i;
						break;
					}
				EndListBox();
			}

			bool showWindow(string s)
			{
				if (windowShow)
				{
					Begin(name.c_str(), &windowShow);
					for (size_t i = 0; i < selectedData.size(); i++)
					{
						Text(labels[i].c_str()); SameLine(); Text(selectedData.strs[i].c_str());
					}
					auto res = Button(s.c_str());
					End();
					return res;
				}
				return false;
			}

		};
	}
}