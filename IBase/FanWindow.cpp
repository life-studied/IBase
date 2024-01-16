#include "FanWindow.h"
#include "imgui.h"
#include "LoginWindow.h"
#include "sqlpre.h"
#include "MysqlOP.h"
#include <tuple>
#include "ChildWindow.hpp"
#include <sstream>
#include "MessageBox.h"

using namespace std;
using namespace ImGui;
using namespace SqlStr;
using namespace DBConn::MysqlOP;
using namespace IBase::WidgetTools;

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
					auto lastName = fandata.strs[1];
					fandata.copy();
					MysqlOP<fan>::query(paddingSql("UPDATE fans SET name = '?', sex = '?', age = ? , job = '?', degree = '?'\
						WHERE id = ? ", fandata.strs[1], fandata.strs[2], fandata.strs[3], fandata.strs[4], fandata.strs[5], fandata.strs[0]));
					MysqlOP<fan>::query(paddingSql("UPDATE account SET username='?' WHERE username='?'", fandata.strs[1], lastName));
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
			static vector<ConcertData> res_concert;
			static vector<BandData> res_band;
			static vector<AlbumData> res_album;
			static vector<SongData> res_song;
			static ChildWindow concert_child_window(&res_concert, u8"演唱会", { u8"演唱会名：",u8"时间：",u8"地点：",u8"乐队名：" });
			static ChildWindow album_child_window(&res_album, u8"专辑", { u8"专辑名：",u8"时间：",u8"介绍：",u8"乐队名：" });
			static ChildWindow band_child_window(&res_band, u8"乐队", { u8"队名：",u8"创建时间：",u8"介绍：",u8"队长：" });
			static ChildWindow song_child_window(&res_song, u8"歌曲", { u8"歌曲名：",u8"作者名：",u8"专辑名：" });
			InputText(u8" ", searchBox, IM_ARRAYSIZE(searchBox)); SameLine(); isSearchClick = Button(u8"搜索");
			if (isSearchClick)
			{
				auto res = searchByName(searchBox);
				res_concert = get<0>(res);
				res_album = get<1>(res);
				res_song = get<2>(res);
				res_band = get<3>(res);
			}
			concert_child_window.showList();
			album_child_window.showList();
			band_child_window.showList();
			song_child_window.showList();

			auto like_concert = concert_child_window.showWindow(u8"参加");
			auto like_album = album_child_window.showWindow(u8"喜欢");
			auto like_band = band_child_window.showWindow(u8"喜欢");
			auto like_song = song_child_window.showWindow(u8"喜欢");

			if (like_concert)
				insertLikeConcert(concert_child_window.selected_str_by_index(0));
			if (like_album)
				insertLikeAlbum(album_child_window.selected_str_by_index(0));
			if (like_band)
				insertLikeBand(band_child_window.selected_str_by_index(0));
			if (like_song)
				insertLikeSong(song_child_window.selected_str_by_index(0));
			static EvalutionData e_data;
			
			if(album_child_window.ifChanged())
				e_data = check_evalution(album_child_window.selected_str_by_index(0));

			// evaluate the album window
			if (album_child_window.ifClicked())
			{
				showEvaluaion(album_child_window.selected_str_by_index(0), e_data);
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

void IBase::IWindows::FanWindow::insertLikeBand(string name)
{
	MysqlOP<fan>::query(paddingSql("INSERT INTO bandlikes(fanid,bandid)\
		VALUES('?', (SELECT id FROM band WHERE band.name = '?'))", fandata.strs[0], name));
}

void IBase::IWindows::FanWindow::insertLikeAlbum(string name)
{
	MysqlOP<fan>::query(paddingSql("INSERT INTO albumlikes(fanid,albumid)\
		VALUES('?', (SELECT id FROM album WHERE album.name = '?'))", fandata.strs[0], name));
	initAlbumData();
}

void IBase::IWindows::FanWindow::insertLikeSong(string name)
{
	MysqlOP<fan>::query(paddingSql("INSERT INTO songlikes(fanid,songid)\
		VALUES('?', (SELECT id FROM songs WHERE songs.name = '?'))", fandata.strs[0], name));
	initSongData();
}

void IBase::IWindows::FanWindow::insertLikeConcert(string name)
{
	MysqlOP<fan>::query(paddingSql("INSERT INTO attendconcert(fanid,concertid)\
		VALUES('?', (SELECT id FROM concert WHERE concert.name = '?'))", fandata.strs[0], name));
	initConcertData();
}

IBase::IWindows::FanWindow::EvalutionData IBase::IWindows::FanWindow::check_evalution(string album_name)
{
	EvalutionData res{};
	auto table = MysqlOP<fan>::query(paddingSql("SELECT album.name, evaluation.score, evaluation.evaluation FROM evaluation\
		LEFT JOIN album ON evaluation.albumid = album.id\
		WHERE evaluation.fanid = ? AND evaluation.albumid = (select id from album WHERE name = '?')", fandata.strs[0], album_name));
	
	if (table.content.empty())
		return {};
	else
	{
		for (int i = 0; i < table.content[0].size(); i++)
		{
			res.strs[i] = table.content[0][i];
		}
		res.reset();
	}
	return res;
}

tuple<vector<IBase::IWindows::FanWindow::ConcertData>,
	vector<IBase::IWindows::FanWindow::AlbumData>, 
	vector<IBase::IWindows::FanWindow::SongData>, 
	vector<IBase::IWindows::FanWindow::BandData>> 
IBase::IWindows::FanWindow::searchByName(string s)
{
	vector<ConcertData> res_concert_list;
	vector<AlbumData> res_album_list;
	vector<SongData> res_song_list;
	vector<BandData> res_band_list;

	auto concert_info_list = MysqlOP<fan>::query(paddingSql(
		"SELECT concert.`name`,concert.time,concert.place,band.`name`\
			FROM concert\
			LEFT JOIN band ON band.id = concert.bandid\
			WHERE concert.name Like '%?%' ",s));
	for (auto& line : concert_info_list.content)
	{
		ConcertData temp{};
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		res_concert_list.push_back(temp);
	}

	auto album_info_list = MysqlOP<fan>::query(paddingSql(
		"SELECT ab.`name`,ab.time,ab.intro,b.`name` bandname FROM album ab,band b\
		WHERE ab.bandid = b.id AND ab.`name` LIKE '%?%'; ", s));
	for (auto& line : album_info_list.content)
	{
		AlbumData temp{};
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		res_album_list.push_back(temp);
	}

	auto song_info_list = MysqlOP<fan>::query(paddingSql(
		"SELECT songs.name,member.`name` authorname,album.`name` albumname FROM songs\
		LEFT JOIN member ON songs.authorid = member.id\
		LEFT JOIN album ON songs.albumid = album.id\
		LEFT JOIN songlikes ON songlikes.songid = songs.id\
		WHERE songs.name LIKE '%?%'; ", s));
	for (auto& line : song_info_list.content)
	{
		SongData temp{};
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		res_song_list.push_back(temp);
	}

	auto band_info_list = MysqlOP<fan>::query(paddingSql(
		"select band.name,band.createtime,band.intro,band.leader from band \
		WHERE band.name LIKE '%?%'", s));
	for (auto& line : band_info_list.content)
	{
		BandData temp{};
		for (size_t i = 0; i < temp.size(); i++)
			temp.strs[i] = line[i];
		res_band_list.push_back(temp);
	}

	return { res_concert_list,res_album_list,res_song_list,res_band_list };

}

void IBase::IWindows::FanWindow::showEvaluaion(string album_name, EvalutionData& e_data)
{
	
	Begin(u8"评价专辑");
	
	static bool isChanging = false;
	static bool showTip = false;
	if (!isChanging)
	{
		Text(u8"评分："); SameLine(); Text(e_data.strs[1].c_str());
		Text(u8"评论："); SameLine(); Text(e_data.strs[2].c_str());
		if (Button(u8"修改"))
			isChanging = true;
	}
	else
	{
		InputText(u8"评分", e_data.boxes[1], IM_ARRAYSIZE(e_data.boxes[1]));
		InputText(u8"评论", e_data.boxes[2], IM_ARRAYSIZE(e_data.boxes[2]));
		if (Button(u8"确定"))
		{
			auto checkillegal = [](string s)
			{
				stringstream ss{ s };
				int data;
				ss >> data;
				if (data >= 1 && data <= 5)
					return data;
				else
					return -1;
			};

			if (checkillegal(e_data.boxes[1]) == -1)
			{
				showTip = true;
			}
			else
			{
				e_data.copy();
				// insert or update
				if (e_data.strs[1].empty())
				{
					MysqlOP<fan>::query(paddingSql("insert into evaluation(fanid,score,evaluation,albumid) \
					values(?, ?, '?', (select id from album WHERE name = '?'))",
						fandata.strs[0], e_data.strs[1], e_data.strs[2], album_name));
				}
				else
				{
					MysqlOP<fan>::query(paddingSql("UPDATE evaluation set score=?, evaluation='?'\
						WHERE fanid = ? AND albumid = (select id from album WHERE name = '?')",
						e_data.strs[1], e_data.strs[2], fandata.strs[0], album_name));
				}

				isChanging = false;
				
			}

		}
	}
	if (showTip)
	{
		if (IMMessageBox(u8"评分错误：必须是0-5之间的数字").isClick())
			showTip = false;
	}
	End();
}