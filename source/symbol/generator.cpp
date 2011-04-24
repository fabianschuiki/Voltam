#include "generator.h"

#include <iostream>
#include <sstream>

extern "C" {
	#include "lualib.h"
}

	
SymbolGenerator::SymbolGenerator(std::string name) : name(name)
{
	//Create the Lua state for the generator.
	luaState = lua_open();
	luaL_openlibs(luaState);
	luabind::open(luaState);
	
	//Expose the Symbol class.
	Symbol::bindToLua(luaState);
	
	//Load the generator script.
	std::stringstream file;
	file << "./symbols/" << name << ".lua";
	if (luaL_dofile(luaState, file.str().c_str()) != 0)
		std::cerr << "unable to open lua file «" << file.str() << "»" << std::endl;
}

SymbolGenerator::~SymbolGenerator()
{
	if (luaState)
		lua_close(luaState);
}



Symbol::ptr SymbolGenerator::generateSymbol()
{
	return generateSymbol("");
}

Symbol::ptr SymbolGenerator::generateSymbol(std::string arguments)
{
	try {
		//Call the Lua function to synthesize the given symbol.
		assert(luaState);
		Symbol::ptr symbol = luabind::call_function<Symbol::ptr>(luaState, "main", arguments);
		return symbol;
	}
	catch (luabind::error& e) {
		std::cerr << "unable to generate symbol «" << name << "» with arguments «" << arguments << "»: " << e.what() << std::endl;
		std::cerr << " -- " << lua_tostring(luaState, -1) << std::endl; lua_pop(luaState, 1);
	}
	return Symbol::ptr();
}

