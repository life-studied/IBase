#pragma once
#include "Data.hpp"
#include <string>
#include <vector>
namespace IBase
{
	namespace WidgetTools
	{
		using std::string;
		using namespace Data;
		class EvaluationListWindow
		{
		public:
			using EvalutionData = VData<4>;
			void showWindow(string name, bool &show);
		private:
			string lastName;
			bool show = false;
			vector<EvalutionData> evaluations;
			void SelectByName();
		};
	}
}