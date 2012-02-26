#include "SymbolTerminal.h"

using namespace lib;


void SymbolTerminal::fromStack(lua_State * L, int index)
{
	//Iterate through the table.
	for (lua_pushnil(L); lua_next(L, index-1); lua_pop(L, 1)) {
		std::string key(lua_tostring(L, -2));
		if (key == "name") { name = lua_tostring(L, -1); }
		if (key == "pos")  { pos.fromStack(L, -1); }
		if (key == "dir")  { dir.fromStack(L, -1); }
	}
}
