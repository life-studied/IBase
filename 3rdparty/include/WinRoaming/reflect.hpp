#pragma once
#include <string>
#include <map>
#include <functional>
#include "Singleton.hpp"
namespace reflect
{
	using namespace std;
	
	template <typename T>
	class ClassFactory
	{
		using createFunc = function<T*()>;

	public:
		void register_class(const string& className, createFunc method)
		{
			classMap[className] = method;
		}
		T* create_class(const string& className)
		{
			auto it = classMap.find(className);
			if (it != classMap.end()) return it->second();
			else return nullptr;
		}
	private:
		map<string, createFunc> classMap;
	};

	template <typename T>
	using singleFactory = Singleton<ClassFactory<T>>;
}