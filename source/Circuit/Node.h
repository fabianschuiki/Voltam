#pragma once
#include <gc_cpp.h>
#include <set>
#include "../Geometry/Geometry.h"


namespace Circuit
{
	class Node : public gc
	{
		public:
			Node();
			
			Geometry::Geometry & getGeometry();
			void invalidateGeometry();
			
		protected:
			Geometry::Geometry geometry;
			bool geometry_valid;
			virtual void generateGeometry() { geometry_valid = true; }
	};
}
