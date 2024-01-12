#include "MemberWindow.h"
#include "imgui.h"
#include "MysqlOP.h"
#include "sqlpre.h"
#include "LoginWindow.h"
#include "helperWindows.hpp"
#include "ChildWindow.hpp"

using namespace DBConn::MysqlOP;
using namespace SqlStr;
using namespace std;
using namespace ImGui;
using namespace IBase::helperWindows;
using namespace IBase::WidgetTools;

string IBase::IWindows::MemberWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
    static bool clear = false;
    static bool isQuitBand = false;
    static bool isAttendBand = false;
    static bool isBackBand = false;
    static string account{}, password{};
    if (!clear)
    {
        account = ((LoginWindow*)(windowlist["Login"]))->getAccount();
        password = ((LoginWindow*)(windowlist["Login"]))->getPass();
        init(account, password);
        ((LoginWindow*)(windowlist["Login"]))->clear();
        clear = true;
    }
	bool isOpen = true;
    static ListWindow<0,3> newsWindow("news", news);
    static ListWindow<1,7> membersWindow("members", members);
    static ListWindow<1,5> albumsWindow("albums", albums);
    static ListWindow<0,5> fansWindow("fans", fans);
    static ListWindow<0,3> concertsWindow("concerts", concerts);
	Begin("Member", &isOpen);
    if (!InBand)
        Text(u8"已退出！");
    if (BeginTabBar(u8"乐队"))
    {
        if (BeginTabItem(u8"主页"))
        {
            static const string lables[] = { u8"乐队名：",u8"乐队介绍：",u8"新闻" };
            Text(lables[0].c_str()); SameLine(); Text(banddata.strs[1].c_str());
            Text(lables[1].c_str()); SameLine(); Text(banddata.strs[3].c_str());
            Text(lables[2].c_str());
            newsWindow.showList();
            EndTabItem();
        }

        if (BeginTabItem(u8"成员"))
        {
            membersWindow.showList();
            EndTabItem();
        }

        if (BeginTabItem(u8"专辑"))
        {
            albumsWindow.showList();
            EndTabItem();
        }

        if (BeginTabItem(u8"歌迷"))
        {
            fansWindow.showList();
            EndTabItem();
        }

        if (BeginTabItem(u8"演唱会"))
        {
            concertsWindow.showList();
            EndTabItem();
        }
        if (BeginTabItem(u8"其它"))
        {
            if (InBand)
                isQuitBand = Button(u8"退出该乐队");
            else
            {
                isAttendBand = Button(u8"加入新乐队");
                isBackBand = Button(u8"回归乐队");
				static bool showAttend = false;
				if (isAttendBand)
				{
					showAttend = true;
				}
				if (showAttend)
				{
                    if (attendBand())
                    {
                        isOpen = false;
                    }
						
				}

            }
                
            EndTabItem();
        }

        EndTabBar();
    }

	

	End();
    newsWindow.showWindow({ u8"名称：",u8"时间：",u8"介绍/地点：" }, {0,1,2});
    membersWindow.showWindow({ u8"姓名：", u8"性别：", u8"职责：",u8"加入时间",u8"离开时间",u8"所属乐队："}, {1,2,3,4,5,6});
    albumsWindow.showWindow({ u8"专辑名称：",u8"发售时间：",u8"介绍：",u8"主唱乐队：" }, { 1,2,3,4 });
    fansWindow.showWindow({ u8"粉丝姓名：",u8"性别：",u8"年龄：",u8"职业：",u8"学历：" }, { 0,1,2,3,4 });
    concertsWindow.showWindow({ u8"演唱会名称：",u8"地点",u8"时间" }, { 0,1,2 });

    if (isQuitBand)
    {
        quitBand();
        isOpen = false;
    }
    if (isBackBand)
    {
        backBand();
        isOpen = false;
    }
    if (!isOpen)
    {
        clear = false;
        isQuitBand = false;
        isAttendBand = false;
        isBackBand = false;
        clearAll();
        account.clear();
        password.clear();
        return parent;
    }
	return getName();
}

void IBase::IWindows::MemberWindow::init(string account, string password)
{
    initMember(account, password);
    if (InBand)
    {
        initBand();
        initNews();
        initAllMembers();
        initAlbums();
        initFans();
        initConcerts();
    }
}

void IBase::IWindows::MemberWindow::initMember(string account, string password)
{
    auto sql = paddingSql("select username from account where account='?'", account);
    auto table = MysqlOP<member>::query(sql);
    auto username = table.content[0][0];
    auto information = MysqlOP<member>::query(paddingSql("select * from member where name='?'", username));
    for (size_t i = 0; i < memberdata.size(); i++)
        memberdata.strs[i] = information.content[0][i];
    memberdata.reset();
    if (!memberdata.strs[5].empty())
    {
        InBand = false;
    }
    else
        InBand = true;
}

void IBase::IWindows::MemberWindow::initAllMembers()
{
    auto sql = paddingSql("select * from member where bandid=?", memberdata.strs[6]);
    auto information = MysqlOP<member>::query(sql);
    for (size_t i = 0; i < information.content.size(); i++)
    {
        MemberData temp{};
        for (size_t j = 0; j < MemberData::size(); j++)
        {
            temp.strs[j] = information.content[i][j];
        }
        members.push_back(temp);
    }
}

void IBase::IWindows::MemberWindow::initBand()
{
    auto sql = paddingSql("select * from band where band.id=?", memberdata.strs[6]);
    auto information = MysqlOP<member>::query(sql);
    for (size_t i = 0; i < banddata.size(); i++)
        banddata.strs[i] = information.content[0][i];
    banddata.reset();
}

void IBase::IWindows::MemberWindow::initNews()
{
    auto sql = paddingSql("SELECT * FROM\
    (\
        SELECT album.`name`,album.time happentime, album.intro\
        FROM album WHERE album.bandid = ?\
        UNION\
        SELECT concert.`name`,concert.time happentime, concert.place\
        FROM concert WHERE concert.bandid = ?\
    ) res\
        ORDER BY res.happentime DESC", banddata.strs[0], banddata.strs[0]);
    auto information = MysqlOP<member>::query(sql);
    for (size_t i = 0; i < information.content.size(); i++)
    {
        NewData temp{};
        for (size_t j = 0; j < NewData::size(); j++)
        {
            temp.strs[j] = information.content[i][j];
        }
        news.push_back(temp);
    }
}

void IBase::IWindows::MemberWindow::initAlbums()
{
    auto sql = paddingSql("select * from album where album.bandid=?", memberdata.strs[6]);
    auto information = MysqlOP<member>::query(sql);
    for (size_t i = 0; i < information.content.size(); i++)
    {
        AlbumData temp{};
        for (size_t j = 0; j < AlbumData::size(); j++)
        {
            temp.strs[j] = information.content[i][j];
        }
        albums.push_back(temp);
        albums[i].reset();
    }
}

void IBase::IWindows::MemberWindow::initFans()
{
    auto sql = paddingSql(
        "select fans.`name`,fans.sex,fans.age,fans.job,fans.degree \
        from fans\
        LEFT JOIN bandlikes ON fans.id = bandlikes.fanid\
    where bandlikes.bandid = ? ", memberdata.strs[6]);
    auto information = MysqlOP<member>::query(sql);
    for (size_t i = 0; i < information.content.size(); i++)
    {
        FanData temp{};
        for (size_t j = 0; j < FanData::size(); j++)
        {
            temp.strs[j] = information.content[i][j];
        }
        fans.push_back(temp);
        fans[i].reset();
    }
}

void IBase::IWindows::MemberWindow::initConcerts()
{
    auto sql = paddingSql("SELECT concert.`name`,concert.place,concert.time FROM concert WHERE concert.bandid=?", memberdata.strs[6]);
    auto information = MysqlOP<member>::query(sql);
    for (size_t i = 0; i < information.content.size(); i++)
    {
        ConcertData temp{};
        for (size_t j = 0; j < ConcertData::size(); j++)
        {
            temp.strs[j] = information.content[i][j];
        }
        concerts.push_back(temp);
        concerts[i].reset();
    }
}

void IBase::IWindows::MemberWindow::quitBand()
{
    auto sql = paddingSql("UPDATE member SET member.leavetime=NOW() WHERE member.id=?", memberdata.strs[0]);
    MysqlOP<member>::query(sql);
}

void IBase::IWindows::MemberWindow::clearAll()
{
    members.clear();
    news.clear();
    albums.clear();
    fans.clear();
    concerts.clear();
}

void IBase::IWindows::MemberWindow::backBand()
{
    auto sql = paddingSql("UPDATE member SET member.leavetime=NULL AND member.jointime=NOW() WHERE member.id=?", memberdata.strs[0]);
    MysqlOP<member>::query(sql);
}

bool IBase::IWindows::MemberWindow::attendBand()
{
    static vector<BandData> band_data = []() 
    {
        vector<BandData> res_band_list;
		auto band_info_list = MysqlOP<fan>::query(paddingSql("select * from band"));
		for (auto& line : band_info_list.content)
		{
			BandData temp{};
			for (size_t i = 0; i < temp.size(); i++)
				temp.strs[i] = line[i];
			res_band_list.push_back(temp);
		}
        return res_band_list;
    }();

    static ChildWindow band_child_window(&band_data, u8"所有乐队", { u8"队伍编号：", u8"队名：",u8"创建时间：",u8"介绍：",u8"队长："});
    band_child_window.showList(1);
    if (band_child_window.showWindow(u8"加入"))
    {
        auto sql = paddingSql("UPDATE member SET member.leavetime=NULL, \
            member.jointime=NOW(), \
            member.bandid=(SELECT id FROM band WHERE band.name='?') \
            WHERE member.id=?", band_child_window.selected_str_by_index(1) ,memberdata.strs[0]);
        MysqlOP<member>::query(sql);
        return true;
    }

    return false;

}
