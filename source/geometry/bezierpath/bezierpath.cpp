#include "bezierpath.h"

using namespace Voltam::Geometry;


void BezierPath::MoveToOperation::execute(const Cairo::RefPtr<Cairo::Context> & cr) const
{
	cr->move_to(p.x, p.y);
}

void BezierPath::LineToOperation::execute(const Cairo::RefPtr<Cairo::Context> & cr) const
{
	cr->line_to(p.x, p.y);
}

void BezierPath::CurveToOperation::execute(const Cairo::RefPtr<Cairo::Context> & cr) const
{
	cr->curve_to(c1.x, c1.y, c2.x, c2.y, p.x, p.y);
}

void BezierPath::CloseOperation::execute(const Cairo::RefPtr<Cairo::Context> & cr) const
{
	cr->close_path();
}



const BezierPath::Operations & BezierPath::getOperations() const
{
	return operations;
}



void BezierPath::moveTo(double2 point)
{
	SmartPointer<MoveToOperation> op = new MoveToOperation();
	op->p = point;
	operations.push_back(op);
}

void BezierPath::lineTo(double2 point)
{
	SmartPointer<LineToOperation> op = new LineToOperation();
	op->p = point;
	operations.push_back(op);
}

void BezierPath::curveTo(double2 point, double2 controlPoint1, double2 controlPoint2)
{
	SmartPointer<CurveToOperation> op = new CurveToOperation();
	op->p = point;
	op->c1 = controlPoint1;
	op->c2 = controlPoint2;
	operations.push_back(op);
}

void BezierPath::close()
{
	operations.push_back(new CloseOperation());
}



void BezierPath::execute(const Cairo::RefPtr<Cairo::Context> & cr) const
{
	for (Operations::const_iterator it = operations.begin(); it != operations.end(); it++)
		(*it)->execute(cr);
}



void BezierPath::moveTo(double x, double y)
{
	moveTo(double2(x, y));
}

void BezierPath::lineTo(double x, double y)
{
	lineTo(double2(x, y));
}

void BezierPath::curveTo(double x, double y, double c1x, double c1y, double c2x, double c2y)
{
	curveTo(double2(x, y), double2(c1x, c1y), double2(c2x, c2y));
}



void BezierPath::rect(const rectd & r)
{
	moveTo(r.minXminY());
	lineTo(r.maxXminY());
	lineTo(r.maxXmaxY());
	lineTo(r.minXmaxY());
	close();
}

void BezierPath::rect(const double2 & origin, const double2 & size)
{
	rect(rectd(origin, size));
}

void BezierPath::rect(double x, double y, double w, double h)
{
	rect(rectd(x, y, w, h));
}

