#pragma once
#include <gc_cpp.h>
#include <map>
#include <set>
#include "../Geometry/Geometry.h"


namespace Circuit
{
	class Node : public gc
	{
	public:
		typedef std::map<std::string, Geometry::Path::Set> Layers;
	
		Node();
		
		Layers & getLayers();
		
		void invalidate();
		
	protected:
		Layers layers;
		
		bool valid;
		virtual void update() = 0;
	};
}
