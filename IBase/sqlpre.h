#pragma once
#include <string>

namespace SqlStr
{
	using std::string;
	using std::is_same_v;
	inline string& to_string(string& s) { return s; }

	template<typename...Args>
	string paddingSql(string&& fmt, Args&&...args)
	{
		size_t lookHere = 0;
		size_t foundHere{};
		((foundHere = fmt.find('?', lookHere), fmt.replace(foundHere, 1, args)), ...);
		return fmt;
	}
}
