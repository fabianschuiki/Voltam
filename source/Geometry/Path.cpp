#include <objlua/class.h>

#include "../Logger.h"
#include "Path.h"

using namespace Geometry;


Path::Path()
{
	stroke = false;
	fill   = false;
	close  = false;
}

void Path::fromStack(lua_State * L, int index)
{
	//Iterate through the table.
	bool move = true;
	for (lua_pushnil(L); lua_next(L, index-1); lua_pop(L, 1))
	{
		//If the field is a string, we treat it as an option.
		if (lua_isstring(L, -1)) {
			std::string opt(lua_tostring(L, -1));
			LOG(DEBUG, "option '%s'", opt.c_str());
			if (opt == "stroke") stroke = true;
			if (opt == "fill")   fill   = true;
			if (opt == "close")  close  = true;
		}
		
		//Otherwise we treat the value as path node.
		else {
			double2 p;
			p.fromStack(L, -1);
			nodes.push_back((Node){p, move});
			move = false;
			LOG(DEBUG, "node '%s'", p.description().c_str());
		}
	}
}
