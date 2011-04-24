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
	return generateSymbol(Symbol::Arguments());
}

Symbol::ptr SymbolGenerator::generateSymbol(Symbol::Arguments arguments)
{
	try {
		//Convert the arguments to a Lua table object.
		luabind::object argTable = luabind::newtable(luaState);
		for (Symbol::Arguments::const_iterator it = arguments.begin(); it != arguments.end(); it++)
			argTable[it->first] = it->second;
		
		//Call the Lua function to generate the symbol.
		Symbol::ptr symbol = luabind::call_function<Symbol::ptr>(luaState, "main", argTable);
		return symbol;
	}
	catch (luabind::error& e) {
		std::cerr << "unable to generate symbol «" << name << "»: " << e.what() << std::endl;
		std::cerr << " -- " << lua_tostring(luaState, -1) << std::endl; lua_pop(luaState, 1);
	}
	return Symbol::ptr();
}

