#pragma once
#include "Data.hpp"
#include "imgui.h"
#include <optional>

namespace IBase
{
	namespace WidgetTools
	{
		using namespace Data;
		using namespace ImGui;
		using std::optional;
		// basic template
		template<typename T>
		class AddNewWindow;

		// 发布窗口
		// 模板特化VData
		template<size_t v_num>
		class AddNewWindow<VData<v_num>>
		{
		public:
			AddNewWindow(vector<string> _labels) : labels(_labels)
			{
				data.reset();
			}

			void show()
			{
				if (Button(u8"发布"))
				{
					showWindow = true;
				}

				if (showWindow)
				{
					Begin(u8"发布", &showWindow);
					size_t idx = 0;
					for (auto& i : labels)
					{
						InputText(i.c_str(), data.boxes[idx], IM_ARRAYSIZE(data.boxes[idx])); idx++;
					}

					if (Button(u8"确定"))
					{
						showWindow = false;
						hasData = true;
						data.copy();
					}
					End();
				}

			}


			optional<VData<v_num>> getData()
			{
				auto res = hasData;
				hasData = false;
				if (!res)
				{
					return nullopt;
				}
				else
				{
					auto add_data = data;
					data.clear();
					return { add_data };
				}
			}

		private:
			bool showWindow = false;
			bool hasData = false;
			VData<v_num> data;
			vector<string> labels;

		};
	}
}