#include <exception>
#include "AdminWindow.h"
#include "imgui.h"
#include "MysqlOP.h"
#include "FanWindow.h"
#include "MemberWindow.h"
#include "LoginWindow.h"
#include "sqlpre.h"
using namespace ImGui;
using namespace DBConn::MysqlOP;
using namespace SqlStr;
std::string IBase::IWindows::AdminWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	static bool clear = false;
	if (!clear)
	{
		clear = true;
		((LoginWindow*)(windowlist["Login"]))->clear();
	}
	bool isOpen = true;
	Begin("Admin", &isOpen);
	Text(u8"用户"); SameLine(); Text(u8"身份");
	auto line_account = [&](const char* username, const char* permission, size_t& id)
    {
		string ch_per{};
		if (string(permission) == "Member")
			ch_per = u8"乐队成员";
		else if (string(permission) == "Fan")
			ch_per = u8"粉丝";
		else
			throw std::invalid_argument(u8"权限异常");
		Text(username); SameLine(); Text(ch_per.c_str()); SameLine();
		PushID(id++);
        auto res = Button(u8"登录");
		PopID();
		return res;
    };
	static const string sql = "select username, permission from account where permission!='Admin'";
	static auto table = MysqlOP<root>::query(sql);
	static bool isClick = false;
	static string permission{"Fan"};
	static string username{};
	size_t id = 0;
	for (auto& line : table.content)
	{
		if (line_account(line[0].c_str(),line[1].c_str(),id))
		{
			isClick = true;
			permission = line[1];
			username = line[0];
		}
	}
	End();

	if (isClick)
	{
		isClick = false;
		auto sql = paddingSql("select account,password from account where username='?' AND permission='?'", username, permission);
		auto table = MysqlOP<root>::query(sql);
		auto* lw = ((LoginWindow*)(windowlist["Login"]));
		lw->setPass(table.content[0][0]);
		lw->setAccount(table.content[0][1]);
		return permission;
	}
	if (!isOpen) 
	{ 
		clear = false;
		return parent;
	}
	return getName();
}
