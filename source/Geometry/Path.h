#pragma once
#include <gc_cpp.h>
#include <vector>

namespace Geometry
{
	class Path : public gc
	{
		public:
			typedef struct { int64_t x; int64_t y; bool move; } Node; 
			std::vector<Node> nodes;
	};
}
