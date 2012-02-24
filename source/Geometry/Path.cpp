#include <objlua/class.h>

#include "Path.h"

using namespace Geometry;


Path::Path(lua_State* L, const char * className): LuaExposable<Path>(L)
{
	constructLua(className);
}

void Path::expose(LuaState & L)
{
	//Create the class and expose the base functions.
	LuaClass::make(L, "Path");
	LuaExposable::expose(L);
	
	//Register the exposed functions.
	static const luaL_Reg functions[] = {
		{"moveTo", Path::lua_moveTo},
		{"lineTo", Path::lua_lineTo},
		{NULL, NULL}
	};
	luaL_register(L, 0, functions);
	
	//Clean up.
	lua_pop(L, 1);
}

int Path::lua_moveTo(lua_State * L)
{
	return lua_nodeTo(L, true);
}

int Path::lua_lineTo(lua_State * L)
{
	return lua_nodeTo(L, false);
}

int Path::lua_nodeTo(lua_State * L, bool move)
{
	int n = lua_gettop(L);
	if (n == 3) {
		Path * p = fromStack(L, 1);
		assert(p != NULL);
		p->nodes.push_back((Node){Vector(luaL_checknumber(L, 2), luaL_checknumber(L, 3)), move});
	} else {
		luaL_error(L, "got %d arguments, expected 3 (self, x, y)", n);
	}
	return 0;
}

int Path::lua_setFilled(lua_State * L)
{
	return 0;
}

int Path::lua_isFilled(lua_State * L)
{
	return 0;
}
