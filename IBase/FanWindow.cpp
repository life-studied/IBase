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
		auto sql = paddingSql("select username from account where account='?'", account);
		auto table = MysqlOP<fan>::query(sql);
		auto username = table.content[0][0];
		auto information = MysqlOP<fan>::query(paddingSql("select * from fans where name='?'", username));
		fandata.id = information.content[0][0];
		fandata.name = information.content[0][1];
		fandata.sex = information.content[0][2];
		fandata.age = information.content[0][3];
		fandata.job = information.content[0][4];
		fandata.degree = information.content[0][5];
		fandata.reset();
		((LoginWindow*)(windowlist["Login"]))->clear();
		clear = true;

		auto band_info_list = MysqlOP<fan>::query(paddingSql("select band.name,band.createtime,band.intro,band.leader from bandlikes LEFT JOIN band ON bandlikes.bandid=band.id WHERE bandlikes.fanid=?",fandata.id));
		bandlikes.clear();
		for (auto& line : band_info_list.content)
		{
			BandData temp{};
			temp.name = line[0];
			temp.createtime = line[1];
			temp.intro = line[2];
			temp.leader = line[3];
			bandlikes.push_back(temp);
		}

		auto album_info_list = MysqlOP<fan>::query(paddingSql(
			"SELECT ab.`name`,ab.time,ab.intro,b.`name` bandname FROM album ab,band b\
			WHERE ab.bandid = b.id AND b.id IN\
			(\
				SELECT albumid FROM albumlikes\
				WHERE fanid =?)", fandata.id));
		albumlikes.clear();
		for (auto& line : album_info_list.content)
		{
			AlbumData temp{};
			temp.name = line[0];
			temp.time = line[1];
			temp.intro = line[2];
			temp.bandname = line[3];
			albumlikes.push_back(temp);
		}

		auto song_info_list = MysqlOP<fan>::query(paddingSql(
			"SELECT songs.name,member.`name` authorname,album.`name` albumname FROM songs\
			LEFT JOIN member ON songs.authorid = member.id\
			LEFT JOIN album ON songs.albumid = album.id\
			LEFT JOIN songlikes ON songlikes.songid = songs.id\
			WHERE songlikes.fanid = ?", fandata.id));
		songlikes.clear();
		for (auto& line : song_info_list.content)
		{
			SongData temp{};
			temp.name = line[0];
			temp.author = line[1];
			temp.album = line[2];
			songlikes.push_back(temp);
		}

		auto concert_info_list = MysqlOP<fan>::query(paddingSql(
			"SELECT concert.`name`,concert.time,concert.place,band.`name`\
			FROM concert\
			LEFT JOIN band ON band.id = concert.bandid\
			LEFT JOIN attendconcert ON concert.id = attendconcert.concertid\
			WHERE attendconcert.fanid = ? ", fandata.id));
		concertattends.clear();
		for (auto& line : concert_info_list.content)
		{
			ConcertData temp{};
			temp.name = line[0];
			temp.time = line[1];
			temp.place = line[2];
			temp.bandname = line[3];
			concertattends.push_back(temp);
		}
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
				Text(u8"姓名："); SameLine(); Text(fandata.name.c_str());
				Text(u8"性别："); SameLine(); Text(fandata.sex.c_str());
				Text(u8"年龄："); SameLine(); Text(fandata.age.c_str());
				Text(u8"职业："); SameLine(); Text(fandata.job.c_str());
				Text(u8"学历："); SameLine(); Text(fandata.degree.c_str());
				if (Button(u8"修改"))
					isChanging = true;
			}
			else
			{
				InputText(u8"姓名", fandata.nameBox, IM_ARRAYSIZE(fandata.ageBox));
				InputText(u8"性别", fandata.sexBox, IM_ARRAYSIZE(fandata.sexBox));
				InputText(u8"年龄", fandata.ageBox, IM_ARRAYSIZE(fandata.ageBox));
				InputText(u8"职业", fandata.jobBox, IM_ARRAYSIZE(fandata.jobBox));
				InputText(u8"学历", fandata.degreeBox, IM_ARRAYSIZE(fandata.degreeBox));
				if (Button(u8"确定"))
				{
					isChanging = false;
					fandata.copy();
					MysqlOP<fan>::query(paddingSql("UPDATE fans SET name = '?', sex = '?', age = ? , job = '?', degree = '?'\
						WHERE id = ? ", fandata.name, fandata.sex, fandata.age, fandata.job, fandata.degree, fandata.id));
				}
			}
			EndTabItem();
		}
		
		if (BeginTabItem(u8"喜欢"))
		{
			BeginListBox(u8"乐队");
			for(auto& i:bandlikes)
				if (Selectable(i.name.c_str(), true))
				{
					isChildBandWindowShow = true;
					showBandData = i;
				}
			EndListBox();
			BeginListBox(u8"专辑");
			for (auto& i : albumlikes)
				if (Selectable(i.name.c_str(), true))
				{
					isChildAlbumWindowShow = true;
					showAlbumData = i;
				}

			EndListBox();
			BeginListBox(u8"歌曲");
			for (auto& i : songlikes)
				if (Selectable(i.name.c_str(), true))
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
				if (Selectable(i.name.c_str(), true))
				{
					isChildConcertWindowShow = true;
					showConcertData = i;
				}
			EndListBox();

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
		Begin(("Band:"+showBandData.name).c_str(), &isChildBandOpen);
		Text(u8"队名："); SameLine(); Text(showBandData.name.c_str());
		Text(u8"创建时间："); SameLine(); Text(showBandData.createtime.c_str());
		Text(u8"介绍："); SameLine(); Text(showBandData.intro.c_str());
		Text(u8"队长："); SameLine(); Text(showBandData.leader.c_str());

		End();
	}
	if (isChildAlbumWindowShow)
	{
		Begin(("Album:"+showAlbumData.name).c_str(), &isChildAlbumOpen);
		Text(u8"专辑名："); SameLine(); Text(showAlbumData.name.c_str());
		Text(u8"时间："); SameLine(); Text(showAlbumData.time.c_str());
		Text(u8"介绍："); SameLine(); Text(showAlbumData.intro.c_str());
		Text(u8"乐队名："); SameLine(); Text(showAlbumData.bandname.c_str());
		End();
	}
	if (isChildSongWindowShow)
	{
		Begin(("Song:"+showSongData.name).c_str(), &isChildSongOpen);
		Text(u8"歌曲名："); SameLine(); Text(showSongData.name.c_str());
		Text(u8"作者名："); SameLine(); Text(showSongData.author.c_str());
		Text(u8"专辑名："); SameLine(); Text(showSongData.album.c_str());
		End();
	}
	if (isChildConcertWindowShow)
	{
		Begin(("Concert:" + showConcertData.name).c_str(), &isChildConcertOpen);
		Text(u8"演唱会名："); SameLine(); Text(showConcertData.name.c_str());
		Text(u8"时间："); SameLine(); Text(showConcertData.time.c_str());
		Text(u8"地点："); SameLine(); Text(showConcertData.place.c_str());
		Text(u8"乐队名："); SameLine(); Text(showConcertData.bandname.c_str());
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

