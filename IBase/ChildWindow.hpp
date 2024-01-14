#pragma once
#include <optional>
#include "imgui.h"
#include "Data.hpp"
#include <vector>
#include <string>

namespace IBase
{
	namespace WidgetTools
	{
		using std::optional;
		using std::vector;
		using std::string;
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
			bool isChanged = false;
			vector<string> labels;
		public:
			ChildWindow() = default;
			ChildWindow(vector<VData<v_num>>* _data) : data(_data) {}
			ChildWindow(vector<VData<v_num>>* _data, string _window_name, vector<string> _labels) : data(_data), name(_window_name), labels(_labels) {}
		public:
			void setName(string _name) { name = _name; }
			void setLabels(vector<string> _labels) { labels = _labels; }
			void setData(vector < VData<v_num>>* _data) { data = _data; }

			bool ifClicked() 
			{
				return windowShow;
			};

			bool ifChanged()
			{
				bool c = isChanged;
				isChanged = false;
				return c;
			}

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
						isChanged = true;
						selectedData = i;
						break;
					}
				EndListBox();
			}

			bool showWindow(const char* str, bool skip = false)
			{
				string s(str);
				if (windowShow)
				{
					Begin(name.c_str(), &windowShow);
					for (size_t j = (skip?1:0),i = 0; i < labels.size(); i++,j++)
					{
						Text(labels[i].c_str()); SameLine(); Text(selectedData.strs[j].c_str());
					}
					auto res = Button(s.c_str());
					End();
					return res;
				}
				return false;
			}

			void showWindow()
			{
				if (windowShow)
				{
					Begin(name.c_str(), &windowShow);
					for (size_t i = 0; i < labels.size(); i++)
					{
						Text(labels[i].c_str()); SameLine(); Text(selectedData.strs[i].c_str());
					}
					End();
				}
			}

			void showWindow(bool skip)
			{
				if (windowShow)
				{
					Begin(name.c_str(), &windowShow);
					for (size_t j = (skip ? 1 : 0), i = 0; i < labels.size(); i++, j++)
					{
						Text(labels[i].c_str()); SameLine(); Text(selectedData.strs[j].c_str());
					}
					End();
				}
			}

			vector<bool> showWindow(vector<string>&& button_names, bool skip = false)
			{
				vector<bool> res_data{};
				if (windowShow)
				{
					Begin(name.c_str(), &windowShow);
					for (size_t j = (skip ? 1 : 0), i = 0; i < labels.size(); i++, j++)
					{
						Text(labels[i].c_str()); SameLine(); Text(selectedData.strs[j].c_str());
					}
					for (auto& i : button_names)
					{
						auto isClick = Button(i.c_str()); SameLine();
						res_data.push_back(isClick);
					}
					End();
				}
				return res_data;
			}
		};
	}
}