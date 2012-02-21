#include "Symbol.h"
using namespace lib;


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
}

/** Returns whether this symbol is valid, i.e. has a valid Lua object table. */
bool Symbol::isValid() const
{
	return (ref != LUA_NOREF);
}
