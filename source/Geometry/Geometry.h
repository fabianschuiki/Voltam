#pragma once
#include <gc_cpp.h>
#include <map>
#include "Layer.h"

namespace Geometry
{
	class Geometry : public gc
	{
		public:
			typedef std::map<int, Layer *> LayerMap;
			LayerMap layers;
	};
}
