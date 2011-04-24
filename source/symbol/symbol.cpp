#include "symbol.h"
#include <iostream>


void Symbol::bindToLua(lua_State * L)
{
	using namespace luabind;
	module(L)
	[
		class_<Symbol, Symbol::ptr>("Symbol")
			.def(constructor<>())
			.def("debug", &Symbol::debug)
	];
}

void Symbol::debug()
{
	std::cout << "debug!" << std::endl;
}

