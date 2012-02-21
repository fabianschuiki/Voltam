#include "TwoGateNode.h"

#include <iostream>
using namespace std;

using namespace Circuit;
using Geometry::Path;
using Geometry::Layer;


void TwoGateNode::setGateA(const Vector & v)
{
	gateA = v;
	invalidateGeometry();
}

void TwoGateNode::setGateB(const Vector & v)
{
	gateB = v;
	invalidateGeometry();
}

void TwoGateNode::generateGeometry()
{
	cout << "generating geometry" << endl;
	Path * p = new Path;
	p->nodes.push_back((Path::Node){gateA, true});
	p->nodes.push_back((Path::Node){gateB, false});
	
	Layer * l = new Layer;
	l->paths.insert(p);

	geometry.layers[0] = l;
	geometry_valid = true;
}
