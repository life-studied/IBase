#pragma once
#include <string>
#include <unordered_map>
#include "reflect.hpp"
namespace window
{
	using std::string;
	using std::unordered_map;
	
	class Window
	{
	public:
		Window(string _name, string _parent = "") :name(_name), parent(_parent) {}
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;
		virtual string drawNext(unordered_map<string, Window*>& windowlist) = 0;
		virtual string getName() { return name; };
		virtual ~Window() {}
	private:
		string name;
	protected:
		string parent;
	};

	using window_register = reflect::singleFactory<Window>;
}
