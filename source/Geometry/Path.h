#pragma once

#include <gc_cpp.h>
#include <vector>

#include "../Vector.h"


namespace Geometry
{
	class Path : public gc
	{
		public:
			typedef struct { Vector p; bool move; } Node; 
			std::vector<Node> nodes;
			bool fill;
	};
}
