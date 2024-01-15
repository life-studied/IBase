#include "MemberWindow.h"
#include "imgui.h"
#include "MysqlOP.h"
#include "sqlpre.h"
#include "LoginWindow.h"
#include "helperWindows.hpp"
#include "ChildWindow.hpp"
#include "InfoBoxes.h"
#include "AddNewWindow.hpp"
#include "EvaluationListWindow.h"

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
    static ChildWindow news_child_window(&news, u8"新闻", {u8"名称：",u8"时间：",u8"介绍/地点："});
    static ChildWindow members_child_window(&members, u8"成员", { u8"姓名：", u8"性别：", u8"职责：",u8"加入时间",u8"离开时间",u8"所属乐队：" });
    static ChildWindow albums_child_window(&albums, u8"专辑", { u8"专辑名称：",u8"发售时间：",u8"介绍：",u8"主唱乐队：" });
    static ChildWindow concerts_child_window(&concerts,u8"演唱会", { u8"演唱会名称：",u8"地点",u8"时间" });
    static ChildWindow fans_child_window(&fans, u8"粉丝", { u8"粉丝姓名：",u8"性别：",u8"年龄：",u8"职业：",u8"学历：" });
    static ChildWindow songs_child_window(&songs, u8"歌曲", { u8"歌曲名", u8"从属专辑" });

	Begin("Member", &isOpen);
    if (!InBand)
        Text(u8"已退出！");
    if (BeginTabBar(u8"乐队"))
    {
        if (BeginTabItem(u8"主页"))
        {
            static const string lables[] = { u8"乐队名：",u8"乐队介绍：",u8"最新动态（演唱会/歌曲/专辑发布）" };
            Text(lables[0].c_str()); SameLine(); Text(banddata.strs[1].c_str());
            Text(lables[1].c_str()); SameLine(); Text(banddata.strs[3].c_str());
            Text(lables[2].c_str());
            news_child_window.showList();
            EndTabItem();
        }

        if (BeginTabItem(u8"个人信息"))
        {
            static vector<string> self_labels = { u8"编号",u8"姓名",u8"性别",u8"职责",u8"加入时间",u8"离开时间",u8"所属乐队" };
            static InfoBoxes selfInfo(self_labels, &memberdata);
            selfInfo.show();
            if (selfInfo.ToChange())
            {

            }
            if (selfInfo.ToCorrect())
            {
                updateSelfInfo();
            }
            EndTabItem();
        }

        if (BeginTabItem(u8"成员"))
        {
            members_child_window.showList(1);
            EndTabItem();
        }

        if (BeginTabItem(u8"专辑"))
        {
            albums_child_window.showList(1);
            static AddNewWindow<AlbumData> album_add({ u8"专辑名称" ,u8"发售时间" ,u8"介绍" ,u8"主唱乐队" });
            album_add.show();
            auto res = album_add.getData();
            if (res.has_value())
            {
                addAlbum(res.value());
            }
            EndTabItem();
        }

        if (BeginTabItem(u8"歌曲"))
        {
            songs_child_window.showList();
            static AddNewWindow<SongData> song_add({ u8"歌曲名", u8"从属专辑" });
            song_add.show();
            auto res = song_add.getData();
            if (res.has_value())
            {
                addSong(res.value());
            }
            EndTabItem();
        }

        if (BeginTabItem(u8"歌迷"))
        {
            fans_child_window.showList();
            EndTabItem();
        }

        if (BeginTabItem(u8"演唱会"))
        {
            concerts_child_window.showList();
			static AddNewWindow<ConcertData> concert_add({ u8"演唱会名字" ,u8"发售时间" ,u8"地点" });
            concert_add.show();
			auto res = concert_add.getData();
			if (res.has_value())
			{
				addConcert(res.value());
			}
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

	news_child_window.showWindow();
	auto album_b_datas = albums_child_window.showWindow({ u8"查看歌迷", u8"查看评分和评论", u8"删除"}, true);
	members_child_window.showWindow(true);
	auto concert_b_datas = concerts_child_window.showWindow({ u8"查看歌迷",u8"删除" });
	fans_child_window.showWindow();
	auto song_b_datas = songs_child_window.showWindow({ u8"查看歌迷",u8"删除" });


	static vector<FanData> like_fans_album;
	static ChildWindow like_fans_album_child_window(&like_fans_album, u8"粉丝信息", { u8"粉丝姓名：",u8"性别：",u8"年龄：",u8"职业：",u8"学历：" });
	static vector<FanData> like_fans_song;
	static ChildWindow like_fans_song_child_window(&like_fans_song, u8"粉丝信息", { u8"粉丝姓名：",u8"性别：",u8"年龄：",u8"职业：",u8"学历：" });
	static vector<FanData> like_fans_concert;
	static ChildWindow like_fans_concert_child_window(&like_fans_concert, u8"粉丝信息", { u8"粉丝姓名：",u8"性别：",u8"年龄：",u8"职业：",u8"学历：" });

	// 查看album粉丝
	static bool show_album_fan = false;
	if (!album_b_datas.empty())
	{
		if (album_b_datas[0])
			show_album_fan = true;
	}

	if (albums_child_window.ifChanged())
	{
		like_fans_album = searchFansByAlbum(albums_child_window.selected_str_by_index(1));
	}

	if (show_album_fan)
	{
		Begin(u8"查看album相关粉丝", &show_album_fan);
		like_fans_album_child_window.showList();
		like_fans_album_child_window.showWindow();
		End();
	}

	// 查看song粉丝
	static bool show_song_fan = false;
	if (!song_b_datas.empty())
	{
		if (song_b_datas[0])
			show_song_fan = true;
	}

	if (songs_child_window.ifChanged())
	{
		like_fans_song = searchFansBySong(songs_child_window.selected_str_by_index(0));
	}

	if (show_song_fan)
	{
		Begin(u8"查看song相关粉丝", &show_song_fan);
		like_fans_song_child_window.showList();
		like_fans_song_child_window.showWindow();
		End();
	}

	// 查看concert粉丝
	static bool show_concert_fan = false;
	if (!concert_b_datas.empty())
	{
		if (concert_b_datas[0])
			show_concert_fan = true;
	}

	if (concerts_child_window.ifChanged())
	{
		like_fans_concert = searchFansByConcert(concerts_child_window.selected_str_by_index(0));
	}

	if (show_concert_fan)
	{
		Begin(u8"查看concert相关粉丝", &show_concert_fan);
		like_fans_concert_child_window.showList();
		like_fans_concert_child_window.showWindow();
		End();
	}

    // 删除song data
	if (!song_b_datas.empty())
	{
        if (song_b_datas[1])
            deleteSongByName(songs_child_window.selected_str_by_index(0));
	}
    // 删除album data
	if (!album_b_datas.empty())
	{
		if (album_b_datas[2])
			deleteAlbumByName(albums_child_window.selected_str_by_index(1));
	}
    // 删除concert data
	if (!concert_b_datas.empty())
	{
		if (concert_b_datas[1])
			deleteConcertByName(concerts_child_window.selected_str_by_index(0));
	}

    // 查看专辑相关信息
    static EvaluationListWindow evaluation_window;
    static bool album_evalu_show = false;
    if (!album_b_datas.empty())
        if (album_b_datas[1])
            album_evalu_show = true;
    evaluation_window.showWindow(albums_child_window.selected_str_by_index(1), album_evalu_show);

	End();


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
        initSongs();
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
    members.clear();
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
    albums.clear();
    for (size_t i = 0; i < information.content.size(); i++)
    {
        AlbumData temp{};
        for (size_t j = 0; j < AlbumData::size(); j++)
        {
            temp.strs[j] = information.content[i][j];
        }
        temp.reset();
        albums.push_back(temp);
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
    fans.clear();
    for (size_t i = 0; i < information.content.size(); i++)
    {
        FanData temp{};
        for (size_t j = 0; j < FanData::size(); j++)
        {
            temp.strs[j] = information.content[i][j];
        }
        temp.reset();
        fans.push_back(temp);
    }
}

void IBase::IWindows::MemberWindow::initConcerts()
{
    auto sql = paddingSql("SELECT concert.`name`,concert.place,concert.time FROM concert WHERE concert.bandid=?", memberdata.strs[6]);
    auto information = MysqlOP<member>::query(sql);
    concerts.clear();
    for (size_t i = 0; i < information.content.size(); i++)
    {
        ConcertData temp{};
        for (size_t j = 0; j < ConcertData::size(); j++)
        {
            temp.strs[j] = information.content[i][j];
        }
        temp.reset();
        concerts.push_back(temp);
    }
}

void IBase::IWindows::MemberWindow::initSongs()
{
    auto sql = paddingSql("SELECT name,albumid from songs where authorid=?",memberdata.strs[0]);
    auto table = MysqlOP<member>::query(sql);
    songs.clear();
    for (auto& line : table.content)
    {
        SongData temp;
        for (size_t i = 0; i < SongData::size(); i++)
        {
            temp.strs[i] = line[i];
        }
        temp.reset();
        songs.push_back(temp);
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
    auto sql = paddingSql("UPDATE member SET member.leavetime=NULL, member.jointime=NOW() WHERE member.id=?", memberdata.strs[0]);
    MysqlOP<member>::query(sql);
}

bool IBase::IWindows::MemberWindow::attendBand()
{
    static vector<BandData> band_data = []() 
    {
        vector<BandData> res_band_list;
		auto band_info_list = MysqlOP<member>::query(paddingSql("select * from band"));
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

void IBase::IWindows::MemberWindow::updateSelfInfo()
{
    // update member table and account table
    auto sql = paddingSql("UPDATE member \
                left join account on member.`name`=account.username \
                SET member.name='?',member.sex='?',member.duty='?', account.username='?' WHERE member.id=?",
        memberdata.strs[1],
        memberdata.strs[2],
        memberdata.strs[3],
        memberdata.strs[1],
        memberdata.strs[0]
    );
    MysqlOP<member>::query(sql);
    initAllMembers();
}

void IBase::IWindows::MemberWindow::addAlbum(AlbumData& data)
{
	auto sql = paddingSql("INSERT INTO album(`name`,time,intro,bandid)\
		VALUES('?', NOW(), '?', (SELECT id FROM band WHERE band.name='?'))",data.strs[0],data.strs[2],banddata.strs[1]);
    MysqlOP<member>::query(sql);
    initAlbums();
}

void IBase::IWindows::MemberWindow::addSong(SongData& data)
{
    auto sql = paddingSql("INSERT INTO songs(`name`,authorid,albumid)\
		VALUES('?', ?, (SELECT id FROM album WHERE album.name='?'))", data.strs[0], memberdata.strs[0], data.strs[1]);
	MysqlOP<member>::query(sql);
    initSongs();
}

void IBase::IWindows::MemberWindow::addConcert(ConcertData& data)
{
	auto sql = paddingSql("INSERT INTO concert(`name`,time,place,bandid)\
		VALUES('?', NOW(), '?', ?)", data.strs[0], data.strs[2], banddata.strs[0]);
	MysqlOP<member>::query(sql);
	initConcerts();
}

vector<IBase::IWindows::MemberWindow::FanData> IBase::IWindows::MemberWindow::searchFansBySong(string name)
{
    vector<FanData> fans;
    auto sql = paddingSql("select fans.`name`,fans.sex,fans.age,fans.job,fans.degree from fans\
                LEFT JOIN songlikes ON songlikes.fanid=fans.id\
                LEFT JOIN songs ON songs.id=songlikes.songid\
                WHERE songs.name='?'", name);
    auto table = MysqlOP<member>::query(sql);
    for (auto& line : table.content)
    {
        FanData temp;
        for (size_t i = 0; i < temp.size(); i++)
            temp.strs[i] = line[i];
        fans.push_back(temp);
    }
    return fans;
}

vector<IBase::IWindows::MemberWindow::FanData> IBase::IWindows::MemberWindow::searchFansByConcert(string name)
{
	vector<FanData> fans;
	auto sql = paddingSql("SELECT fans.`name`,fans.sex,fans.age,fans.job,fans.degree \
		FROM fans, attendconcert, concert\
		WHERE fans.id = attendconcert.fanid AND concert.id = attendconcert.concertid AND concert.`name`='?'", name);
	auto table = MysqlOP<member>::query(sql);
	for (auto& line : table.content)
	{
		FanData temp;
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		fans.push_back(temp);
	}
	return fans;
}

vector<IBase::IWindows::MemberWindow::FanData> IBase::IWindows::MemberWindow::searchFansByAlbum(string name)
{
	vector<FanData> fans;
	auto sql = paddingSql("select fans.`name`,fans.sex,fans.age,fans.job,fans.degree from fans\
                LEFT JOIN albumlikes ON albumlikes.fanid=fans.id\
                LEFT JOIN album ON album.id=albumlikes.albumid\
                WHERE album.name='?'", name);
	auto table = MysqlOP<member>::query(sql);
	for (auto& line : table.content)
	{
		FanData temp;
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		fans.push_back(temp);
	}
	return fans;
}

void IBase::IWindows::MemberWindow::deleteSongByName(string name)
{
	MysqlOP<member>::query(paddingSql("DELETE songs,songlikes FROM songs\
        LEFT JOIN songlikes ON songs.id = songlikes.songid \
        WHERE songs.`name`='?'", name));
    initSongs();
}

void IBase::IWindows::MemberWindow::deleteConcertByName(string name)
{
	MysqlOP<member>::query(paddingSql("DELETE attendconcert FROM concert\
		LEFT JOIN attendconcert ON concert.id = attendconcert.concertid\
		WHERE concert.`name`='?'", name));
	MysqlOP<member>::query(paddingSql("DELETE concert FROM concert\
		LEFT JOIN attendconcert ON concert.id = attendconcert.concertid\
		WHERE concert.`name`='?'", name));
	initConcerts();
}

void IBase::IWindows::MemberWindow::deleteAlbumByName(string name)
{
	MysqlOP<member>::query(paddingSql("DELETE album,albumlikes,songs,songlikes FROM album \
        LEFT JOIN albumlikes ON album.id=albumlikes.albumid \
        LEFT JOIN songs ON songs.albumid=album.id \
        LEFT JOIN songlikes ON songlikes.songid=songs.id \
        WHERE album.`name`='?'", name));
	initAlbums();
    initSongs();
}
