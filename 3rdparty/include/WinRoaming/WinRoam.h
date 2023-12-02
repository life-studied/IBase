#pragma once
#include "Window.h"
#include <vector>
#include <unordered_map>
namespace window
{
	using std::vector;
	using std::unordered_map;
	class WinRoam
	{
	public:
		WinRoam(Window* _now) :now(_now) { windows[now->getName()] = now; }
		bool draw()
		{
			if (!now) return false;
			auto next = now->drawNext(windows);
			if (next.empty()) return false;
			auto nextIt = windows.find(next);
			if (nextIt == windows.end())
				windows[next] = window_register::getInstance().create_class(next);
			now = windows[next];
			return true;
		}
		~WinRoam()
		{
			for (auto& i : windows)
			{
				if (i.second)
					delete i.second;
			}
		}
	private:
		Window* now;
		unordered_map<string,Window*> windows;
	};

	
}

