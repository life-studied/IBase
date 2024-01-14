#pragma once
#include <string>
#include <array>
namespace IBase
{
	namespace Data
	{
		using namespace std;
		// Data struct for InputText
		template <size_t N,size_t boxSize=50>
		struct VData
		{
			array<string, N> strs;
			array<char[boxSize], N> boxes = {};
			inline void copy()
			{
				for (size_t i = 0; i < N; i++)
				{
					strs[i] = boxes[i];
				}
			}
			inline void reset()
			{
				for (size_t i = 0; i < N; i++)
				{
					strcpy_s(boxes[i], strs[i].c_str());
				}
			}
			inline static auto size() { return N; }

			inline void clear()
			{
				for (auto& i : strs)
					i.clear();
				reset();
			}
		};

		template <typename T>
		struct ownData
		{
			T data;
			bool owned;
		};

	}
}
