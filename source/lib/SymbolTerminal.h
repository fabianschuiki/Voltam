#pragma once
#include <gc_cpp.h>
#include <objlua/objlua.h>
#include <set>
#include <string>
#include "../Logger.h"
#include "../math/Vector2D.h"

namespace lib
{
	class SymbolTerminal : public gc
	{
	public:
		double2 pos;
		double2 dir;
		std::string name;
		
		typedef std::set<SymbolTerminal *> Set;
		
		void fromStack(lua_State * L, int index);
	};
}
