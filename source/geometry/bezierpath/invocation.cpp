#include "invocation.h"

using namespace Voltam::Geometry;

			
BezierPath::Invocation::Invocation()
{
	stroke = false;
	fill = false;
}

BezierPath::Invocation::Invocation(BezierPath * path)
{
	this->path = path;
	stroke = false;
	fill = false;
}

BezierPath::Invocation::Invocation(BezierPath * path, bool stroke, bool fill)
{
	this->path = path;
	this->stroke = stroke;
	this->fill = fill;
}

void BezierPath::Invocation::draw(const Cairo::RefPtr<Cairo::Context> & cr)
{
	if (!path) return;	
	
	//Execute the bezier path.
	path->execute(cr);
	
	//Stroke, fill or do both.
	if (stroke && fill) {
		cr->fill_preserve();
		cr->stroke();
	}
	else if (stroke) cr->stroke();
	else if (fill)   cr->fill();
}

