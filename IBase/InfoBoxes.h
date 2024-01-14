#pragma once
#include <string>
#include <vector>
#include "Data.hpp"
#include "imgui.h"


namespace IBase
{
	namespace WidgetTools
	{
		using std::vector;
		using std::string;
		using namespace Data;
		using namespace ImGui;

		template<size_t v_num>
		class InfoBoxes
		{
		public:
			InfoBoxes(vector<string> _labels, VData<v_num>* _data);
			void show();
			bool ToChange();
			bool ToCorrect();
		private:
			bool ToCo = false;
			bool ToCh = false;

			bool InChanging = false;
			vector<string> labels;
			VData<v_num>* data;
		};

		template<size_t v_num>
		IBase::WidgetTools::InfoBoxes<v_num>::InfoBoxes(vector<string> _labels, VData<v_num>* _data) : labels(_labels), data(_data)
		{

		}

		template<size_t v_num>
		void IBase::WidgetTools::InfoBoxes<v_num>::show()
		{
			if (!InChanging)
			{
				size_t idx = 0;
				for (auto& i : labels)
				{
					Text(i.c_str()); SameLine(); Text(data->strs[idx++].c_str());
				}
				if (Button(u8"ÐÞ¸Ä"))
				{
					InChanging = true;
					ToCh = true;
				}
			}
			else
			{
				size_t idx = 0;
				for (auto& i : labels)
				{
					InputText(i.c_str(), data->boxes[idx], IM_ARRAYSIZE(data->boxes[idx])); idx++;
				}
				if (Button(u8"È·¶¨"))
				{
					InChanging = false;
					ToCo = true;
					data->copy();
				}
			}
		}

		template<size_t v_num>
		bool IBase::WidgetTools::InfoBoxes<v_num>::ToChange()
		{
			bool res = ToCh;
			ToCh = false;
			return res;
		}

		template<size_t v_num>
		bool IBase::WidgetTools::InfoBoxes<v_num>::ToCorrect()
		{
			bool res = ToCo;
			ToCo = false;
			return res;
		}

	}
}