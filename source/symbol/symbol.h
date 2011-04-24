#pragma once

#include <boost/smart_ptr.hpp>
#include <luabind/luabind.hpp>


class Symbol {
public:
	typedef boost::shared_ptr<Symbol> ptr;
	
	static void bindToLua(lua_State * L);
	void debug();
};

