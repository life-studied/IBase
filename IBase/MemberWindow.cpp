#include "MemberWindow.h"
#include "imgui.h"
#include "MysqlOP.h"
#include "sqlpre.h"
#include "LoginWindow.h"
using namespace DBConn::MysqlOP;
using namespace SqlStr;
using namespace std;
using namespace ImGui;
string IBase::IWindows::MemberWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	
    static bool clear = false;
    static string account{}, password{};
    if (!clear)
    {
        account = ((LoginWindow*)(windowlist["Login"]))->getAccount();
        password = ((LoginWindow*)(windowlist["Login"]))->getPass();
        //auto sql = paddingSql("select ");
        //auto table = MysqlOP<fan>::query(sql);
        ((LoginWindow*)(windowlist["Login"]))->clear();
        clear = true;
    }
	bool isOpen = true;
	Begin("Member", &isOpen);
    if (ImGui::BeginTabBar(u8"乐队"))
    {
        if (ImGui::BeginTabItem(u8"主页"))
        {
            ImGui::Text("This is the content of Tab 1");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(u8"成员"))
        {
            ImGui::Text("This is the content of Tab 2");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(u8"专辑"))
        {
            ImGui::Text("This is the content of Tab 3");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(u8"歌迷"))
        {
            ImGui::Text("This is the content of Tab 4");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(u8"演唱会"))
        {
            ImGui::Text("This is the content of Tab 5");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }


	End();
    if (!isOpen)
    {
        clear = false;
        account.clear();
        password.clear();
        return parent;
    }
	return getName();
}
