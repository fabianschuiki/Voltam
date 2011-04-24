#pragma once

#include <string>
#include <luabind/luabind.hpp>

#include "symbol.h"


class SymbolGenerator {

	const std::string name;
	lua_State * luaState;
	
public:
	typedef boost::shared_ptr<SymbolGenerator> ptr;
	
	SymbolGenerator(std::string name);
	~SymbolGenerator();
	
	Symbol::ptr generateSymbol();
	Symbol::ptr generateSymbol(std::string arguments);
};

