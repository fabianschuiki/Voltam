#include "../Logger.h"
#include "Symbol.h"

using namespace lib;
using Geometry::Path;


Symbol::Symbol(LuaState& L, int index)
:	L(L)
{
	ref = LUA_NOREF;

	//Wrap the index around so that negative indices refer to offsets from the stack top.
	if (index < 0) index += lua_gettop(L) + 1;
	assert(index > 0 && "stack index > 0 required");
	
	//Check whether said stack index is a valid table.
	int type = lua_type(L, index);
	if (type != LUA_TTABLE) {
		//TODO: add proper error handling, maybe even throw an exception here.
		std::cerr << "*** trying to load symbol at index " << index << ", which is a " << lua_typename(L, type) << " instead of a table. stack: " << LuaStack::describe(L) << std::endl;
		return;
	}

	//Keep a reference to the table.
	lua_pushvalue(L, index);
	ref = luaL_ref(L, LUA_REGISTRYINDEX);
	
	//Extract the name.
	lua_pushstring(L, "name");
	lua_gettable(L, -2);
	if (lua_isnil(L, -1)) {
		std::cerr << "*** symbol table does not have a 'name' field. stack: " << LuaStack::describe(L) << std::endl;
		luaL_unref(L, LUA_REGISTRYINDEX, ref);
		ref = LUA_NOREF;
	} else {
		name = lua_tolstring(L, -1, NULL);
	}
	lua_pop(L, 1);
}

/** Initializes the symbol, i.e. resolves symbol inheritance and extracts the symbol name. */
void Symbol::init()
{
	//Push the symbol's table onto the stack.
	lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
	
	//TODO: resolve inheritance
	
	//Get rid of the object table.
	lua_pop(L, 1);
	std::cout << "initialized symbol " << name << std::endl;
	
	//Update the geometry and terminals.
	update();
}

/** Returns whether this symbol is valid, i.e. has a valid Lua object table. */
bool Symbol::isValid() const
{
	return (ref != LUA_NOREF);
}

void Symbol::update()
{
	LOG(INFO, "updating symbol '%s'", name.c_str());
	terminals.clear();
	paths.clear();
	
	//Call the generate() function of the Lua symbol.
	Lua::callFunction(L, "generate", ref, 1);
	
	//Iterate through the returned table and process each entry.
	for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
		lua_pushvalue(L, -2);
		std::string key(lua_tostring(L, -1));
		lua_pop(L, 1);
		
		if (key == "terminals") {
			for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
				SymbolTerminal * t = new SymbolTerminal;
				t->name = std::string(lua_tostring(L, -2));
				t->fromStack(L, -1);
				terminals.insert(t);
			}
		}
		if (key == "paths") {
			for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
				Geometry::Path * p = new Geometry::Path;
				p->fromStack(L, -1);
				paths.insert(p);
			}
		}
	}
	lua_pop(L, 1);
	
	//Dump some statistics.
	LOG(DEBUG, "symbol '%s' has %i terminals, %i paths", name.c_str(), terminals.size(), paths.size());
}
