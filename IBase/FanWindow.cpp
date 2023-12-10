#include "FanWindow.h"
#include "imgui.h"
#include "LoginWindow.h"
#include "sqlpre.h"
#include "MysqlOP.h"
using namespace std;
using namespace ImGui;
using namespace SqlStr;
using namespace DBConn::MysqlOP;
string IBase::IWindows::FanWindow::drawNext(unordered_map<string, Window*>& windowlist)
{
	static bool clear = false;
	if(!clear)
	{
		string account{}, password{};
		account = ((LoginWindow*)(windowlist["Login"]))->getAccount();
		password = ((LoginWindow*)(windowlist["Login"]))->getPass();
		init(account, password);
		((LoginWindow*)(windowlist["Login"]))->clear();
		clear = true;
	}
	bool isOpen = true;
	static bool isChanging = false;
	static bool isChildBandWindowShow = false;
	static bool isChildAlbumWindowShow = false;
	static bool isChildSongWindowShow = false;
	static bool isChildConcertWindowShow = false;
	static BandData showBandData{};
	static AlbumData showAlbumData{};
	static SongData showSongData{};
	static ConcertData showConcertData{};
	Begin("Fan", &isOpen);
	if (BeginTabBar("FanTab"))
	{
		if (BeginTabItem(u8"个人信息"))
		{
			if (!isChanging)
			{
				Text(u8"姓名："); SameLine(); Text(fandata.strs[1].c_str());
				Text(u8"性别："); SameLine(); Text(fandata.strs[2].c_str());
				Text(u8"年龄："); SameLine(); Text(fandata.strs[3].c_str());
				Text(u8"职业："); SameLine(); Text(fandata.strs[4].c_str());
				Text(u8"学历："); SameLine(); Text(fandata.strs[5].c_str());
				if (Button(u8"修改"))
					isChanging = true;
			}
			else
			{
				InputText(u8"姓名", fandata.boxes[1], IM_ARRAYSIZE(fandata.boxes[1]));
				InputText(u8"性别", fandata.boxes[2], IM_ARRAYSIZE(fandata.boxes[2]));
				InputText(u8"年龄", fandata.boxes[3], IM_ARRAYSIZE(fandata.boxes[3]));
				InputText(u8"职业", fandata.boxes[4], IM_ARRAYSIZE(fandata.boxes[4]));
				InputText(u8"学历", fandata.boxes[5], IM_ARRAYSIZE(fandata.boxes[5]));
				if (Button(u8"确定"))
				{
					isChanging = false;
					fandata.copy();
					MysqlOP<fan>::query(paddingSql("UPDATE fans SET name = '?', sex = '?', age = ? , job = '?', degree = '?'\
						WHERE id = ? ", fandata.strs[1], fandata.strs[2], fandata.strs[3], fandata.strs[4], fandata.strs[5], fandata.strs[0]));
				}
			}
			EndTabItem();
		}
		
		if (BeginTabItem(u8"喜欢"))
		{
			BeginListBox(u8"乐队");
			for(auto& i:bandlikes)
				if (Selectable(i.strs[0].c_str(), true))
				{
					isChildBandWindowShow = true;
					showBandData = i;
				}
			EndListBox();
			BeginListBox(u8"专辑");
			for (auto& i : albumlikes)
				if (Selectable(i.strs[0].c_str(), true))
				{
					isChildAlbumWindowShow = true;
					showAlbumData = i;
				}

			EndListBox();
			BeginListBox(u8"歌曲");
			for (auto& i : songlikes)
				if (Selectable(i.strs[0].c_str(), true))
				{
					isChildSongWindowShow = true;
					showSongData = i;
				}

			EndListBox();
			EndTabItem();
		}
		if (BeginTabItem(u8"活动"))
		{
			Text(u8"演唱会");
			BeginListBox(u8"演唱会列表");
			for (auto& i : concertattends)
				if (Selectable(i.strs[0].c_str(), true))
				{
					isChildConcertWindowShow = true;
					showConcertData = i;
				}
			EndListBox();

			EndTabItem();
		}

		if (BeginTabItem(u8"其它"))
		{
			static char searchBox[50]{ u8"请输入搜索条件" };
			static bool isSearchClick = false;
			static vector<ownData<BandData>> searchRes{};
			InputText(u8" ", searchBox, IM_ARRAYSIZE(searchBox)); SameLine(); isSearchClick = Button(u8"搜索");
			if (isSearchClick)
			{
				searchRes.clear();
				// auto band_all_info = MysqlOP<fan>::query("select * from band");
			}
			EndTabItem();
		}
		EndTabBar();
	}
	
	End();
	static bool isChildBandOpen = true;
	static bool isChildAlbumOpen = true;
	static bool isChildSongOpen = true;
	static bool isChildConcertOpen = true;
	if (isChildBandWindowShow)
	{
		isChildBandOpen = true;
		Begin(("Band:"+showBandData.strs[0]).c_str(), &isChildBandOpen);
		static const string labels[] = { u8"队名：",u8"创建时间：",u8"介绍：",u8"队长：" };
		for (size_t i = 0; i < showBandData.size(); i++)
		{
			Text(labels[i].c_str()); SameLine(); Text(showBandData.strs[i].c_str());
		}

		End();
	}
	if (isChildAlbumWindowShow)
	{
		isChildAlbumOpen = true;
		Begin(("Album:"+showAlbumData.strs[0]).c_str(), &isChildAlbumOpen);
		static const string labels[] = { u8"专辑名：",u8"时间：",u8"介绍：",u8"乐队名：" };
		for (size_t i = 0; i < showAlbumData.size(); i++)
		{
			Text(labels[i].c_str()); SameLine(); Text(showAlbumData.strs[i].c_str());
		}
		
		End();
	}
	if (isChildSongWindowShow)
	{
		isChildSongOpen = true;
		Begin(("Song:"+showSongData.strs[0]).c_str(), &isChildSongOpen);
		static const string labels[] = { u8"歌曲名：",u8"作者名：",u8"专辑名："};
		for (size_t i = 0; i < showSongData.size(); i++)
		{
			Text(labels[i].c_str()); SameLine(); Text(showSongData.strs[i].c_str());
		}
		End();
	}
	if (isChildConcertWindowShow)
	{
		isChildConcertOpen = true;
		Begin(("Concert:" + showConcertData.strs[0]).c_str(), &isChildConcertOpen);
		static const string labels[] = { u8"演唱会名：",u8"时间：",u8"地点：",u8"乐队名：" };
		for (size_t i = 0; i < showConcertData.size(); i++)
		{
			Text(labels[i].c_str()); SameLine(); Text(showConcertData.strs[i].c_str());
		}
		End();
	}
	if (!isChildBandOpen)
	{
		isChildBandWindowShow = false;
	}
	if (!isChildAlbumOpen)
	{
		isChildAlbumWindowShow = false;
	}
	if (!isChildSongOpen)
	{
		isChildSongWindowShow = false;
	}
	if (!isChildConcertOpen)
	{
		isChildConcertWindowShow = false;
	}
	if (!isOpen)
	{
		clear = false;
		return parent;
	}
	return getName();
}

void IBase::IWindows::FanWindow::init(string account, string password)
{
	initFanData(account, password);
	initBandData();
	initSongData();
	initAlbumData();
	initConcertData();
}

void IBase::IWindows::FanWindow::initFanData(string account,string password)
{
	
	auto sql = paddingSql("select username from account where account='?'", account);
	auto table = MysqlOP<fan>::query(sql);
	auto username = table.content[0][0];
	auto information = MysqlOP<fan>::query(paddingSql("select * from fans where name='?'", username));
	for (size_t i = 0; i < fandata.size(); i++)
		fandata.strs[i] = information.content[0][i];
	fandata.reset();
}

void IBase::IWindows::FanWindow::initBandData()
{
	auto band_info_list = MysqlOP<fan>::query(paddingSql("select band.name,band.createtime,band.intro,band.leader from bandlikes LEFT JOIN band ON bandlikes.bandid=band.id WHERE bandlikes.fanid=?", fandata.strs[0]));
	bandlikes.clear();
	for (auto& line : band_info_list.content)
	{
		BandData temp{};
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		bandlikes.push_back(temp);
	}
}

void IBase::IWindows::FanWindow::initAlbumData()
{
	auto album_info_list = MysqlOP<fan>::query(paddingSql(
		"SELECT ab.`name`,ab.time,ab.intro,b.`name` bandname FROM album ab,band b\
			WHERE ab.bandid = b.id AND b.id IN\
			(\
				SELECT albumid FROM albumlikes\
				WHERE fanid =?)", fandata.strs[0]));
	albumlikes.clear();
	for (auto& line : album_info_list.content)
	{
		AlbumData temp{};
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		albumlikes.push_back(temp);
	}
}

void IBase::IWindows::FanWindow::initSongData()
{
	auto song_info_list = MysqlOP<fan>::query(paddingSql(
		"SELECT songs.name,member.`name` authorname,album.`name` albumname FROM songs\
			LEFT JOIN member ON songs.authorid = member.id\
			LEFT JOIN album ON songs.albumid = album.id\
			LEFT JOIN songlikes ON songlikes.songid = songs.id\
			WHERE songlikes.fanid = ?", fandata.strs[0]));
	songlikes.clear();
	for (auto& line : song_info_list.content)
	{
		SongData temp{};
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		songlikes.push_back(temp);
	}
}

void IBase::IWindows::FanWindow::initConcertData()
{
	auto concert_info_list = MysqlOP<fan>::query(paddingSql(
		"SELECT concert.`name`,concert.time,concert.place,band.`name`\
			FROM concert\
			LEFT JOIN band ON band.id = concert.bandid\
			LEFT JOIN attendconcert ON concert.id = attendconcert.concertid\
			WHERE attendconcert.fanid = ? ", fandata.strs[0]));
	concertattends.clear();
	for (auto& line : concert_info_list.content)
	{
		ConcertData temp{};
		for(size_t i = 0;i<temp.size();i++)
			temp.strs[i] = line[i];
		concertattends.push_back(temp);
	}
}

