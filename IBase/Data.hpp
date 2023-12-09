#pragma once
#include <string>
namespace IBase
{
	namespace Data
	{
		using namespace std;
		struct FanData
		{
			string id;
			string name;
			char nameBox[50];
			string sex;
			char sexBox[50];
			string age;
			char ageBox[50];
			string job;
			char jobBox[50];
			string degree;
			char degreeBox[50];

			void copy();
			void reset();
		};
		struct BandData
		{
			string name;
			string createtime;
			string intro;
			string leader;
		};

		struct AlbumData
		{
			string name;
			string time;
			string intro;
			string bandname;

		};
		struct SongData
		{
			string name;
			string author;
			string album;

		};
		struct ConcertData
		{
			string name;
			string time;
			string place;
			string bandname;
		};
		inline void FanData::copy()
		{
			name = nameBox;
			age = ageBox;
			sex = sexBox;
			job = jobBox;
			degree = degreeBox;
		}

		inline void FanData::reset()
		{
			strcpy_s(nameBox, name.c_str());
			strcpy_s(ageBox, age.c_str());
			strcpy_s(sexBox, sex.c_str());
			strcpy_s(jobBox, job.c_str());
			strcpy_s(degreeBox, degree.c_str());
		}

	}
}
