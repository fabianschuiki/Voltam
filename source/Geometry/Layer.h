#pragma once
#include <gc_cpp.h>
#include <set>
#include "Path.h"

namespace Geometry
{
	class Layer : public gc
	{
		public:
			typedef std::set<Path *> PathSet;
			PathSet paths;
	};
}
