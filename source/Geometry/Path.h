#pragma once

#include <gc_cpp.h>
#include <set>
#include <vector>

#include "../math/Vector2D.h"


namespace Geometry
{
	class Path : public gc
	{
	public:
		typedef std::set<Path *> Set;
		
		Path();
		
		typedef struct { double2 p; bool move; } Node; 
		std::vector<Node> nodes;
		
		bool fill;
		bool stroke;
		bool close;
		
		void fromStack(lua_State * L, int index);
	};
}
