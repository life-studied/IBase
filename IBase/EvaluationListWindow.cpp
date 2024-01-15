#include "EvaluationListWindow.h"
#include "ChildWindow.hpp"
#include "MysqlOP.h"
#include "sqlpre.h"

using namespace DBConn::MysqlOP;
using namespace SqlStr;

void IBase::WidgetTools::EvaluationListWindow::showWindow(string name, bool &show)
{
	if (name != lastName)
	{
		lastName = name;
		SelectByName();
	}
		
	static ChildWindow evaluation_child_window(&evaluations, u8"评价", {u8"评论人",u8"评分",u8"评价"});
	if (show)
	{
		Begin(u8"评价", &show);
		evaluation_child_window.showList();
		evaluation_child_window.showWindow(u8"评价详情", true);
		End();
	}
}

void IBase::WidgetTools::EvaluationListWindow::SelectByName()
{
	auto table = MysqlOP<fan>::query(paddingSql("SELECT albumid,fans.`name`,score,evaluation\
		FROM album, fans, evaluation\
		WHERE album.id = evaluation.albumid AND evaluation.fanid = fans.id AND album.`name`='?'", lastName));
	evaluations.clear();
	for (auto& line : table.content)
	{
		EvalutionData temp;
		for (auto i = 0; i < EvalutionData::size(); i++)
		{
			temp.strs[i] = line[i];
		}
		temp.reset();
		evaluations.push_back(temp);
	}
}
