#pragma once
#include <objlua/objlua.h>

namespace lib
{
	class Library;
	
	class Symbol
	{
	public:
		LuaState & L;
		Symbol(LuaState & L, int index = -1);
		
		void init();
		bool isValid() const;
		
		const std::string & getName() const { return name; }
		
	protected:
		int ref;
		
		std::string name;
	};
}
