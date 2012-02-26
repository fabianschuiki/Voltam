#include <iostream>

#include "../Geometry/Path.h"
#include "Library.h"
#include "Symbol.h"

using namespace lib;


Library::Library()
{
	//Install the ObjectiveLua class mechanisms.
	LuaClass::install(L);

	//DEBUG: load some symbols
	loadSymbol("../library/resistor.lua");
	loadSymbol("../library/diode.lua");
	
	//Initialize the symbols.
	for (SymbolSet::iterator s = symbols.begin(); s != symbols.end(); s++) {
		(*s)->init();
		symbolsByName[(*s)->getName()] = *s;
	}
}

void Library::loadSymbol(const char * path)
{
	//Execute the script file which returns a list of symbols which we will wrap inside Symbol objects.
	L.dofile(path);

	//Check whether the script's return value is a table.
	int type = lua_type(L, -1);
	if (type != LUA_TTABLE) {
		//TODO: add some proper error handling here
		std::cerr << path << ": return value is not a table" << std::endl;
		return;
	}
	
	//Iterate through the returned table and wrap each entry.
	for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
		Symbol * s = new Symbol(L);
		if (s->isValid()) {
			symbols.insert(s);
		}
	}

	//Pop the table off the stack since it's not needed anymore.
	lua_pop(L, 1);
}
