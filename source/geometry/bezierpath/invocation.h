#pragma once

#include <gtkmm.h>
#include "../../smartpointer.h"
#include "bezierpath.h"


namespace Voltam {
	namespace Geometry {
		class BezierPath::Invocation {
		public:
			SmartPointer<BezierPath> path;
			bool stroke;
			bool fill;
			
			Invocation();
			Invocation(BezierPath * path);
			Invocation(BezierPath * path, bool stroke, bool fill);
			
			void draw(const Cairo::RefPtr<Cairo::Context> & cr);
		};
	}
}

