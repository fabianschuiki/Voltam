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
	boost::shared_ptr<MoveToOperation> op(new MoveToOperation());
	op->p = point;
	operations.push_back(op);
}

void BezierPath::lineTo(double2 point)
{
	boost::shared_ptr<LineToOperation> op(new LineToOperation());
	op->p = point;
	operations.push_back(op);
}

void BezierPath::curveTo(double2 point, double2 controlPoint1, double2 controlPoint2)
{
	boost::shared_ptr<CurveToOperation> op(new CurveToOperation());
	op->p = point;
	op->c1 = controlPoint1;
	op->c2 = controlPoint2;
	operations.push_back(op);
}

void BezierPath::close()
{
	operations.push_back(boost::shared_ptr<CloseOperation>(new CloseOperation()));
}



void BezierPath::execute(const Cairo::RefPtr<Cairo::Context> & cr) const
{
	for (Operations::const_iterator it = operations.begin(); it != operations.end(); it++)
		(*it)->execute(cr);
}
