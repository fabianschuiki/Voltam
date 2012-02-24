#pragma once

#include <gc_cpp.h>
#include <objlua/objlua.h>
#include <vector>

#include "../Vector.h"


namespace Geometry
{
	class Path : public gc, public LuaExposable<Path>
	{
	public:
		OBJLUA_CONSTRUCTOR(Path) {}
		Path(lua_State * L, const char * className);
		static void expose(LuaState & L);
		
		Path() : LuaExposable<Path>(NULL) {}
		
		typedef struct { Vector p; bool move; } Node; 
		std::vector<Node> nodes;
		bool fill;
		
	private:
		static int lua_moveTo(lua_State * L);
		static int lua_lineTo(lua_State * L);
		static int lua_nodeTo(lua_State * L, bool move);
		
		static int lua_setFilled(lua_State * L);
		static int lua_isFilled(lua_State * L);
	};
}
