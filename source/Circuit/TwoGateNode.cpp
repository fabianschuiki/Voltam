#include "TwoGateNode.h"

#include <iostream>
using namespace std;

using namespace Circuit;
using Geometry::Path;
using Geometry::Layer;


void TwoGateNode::setGateA(const double2 & v)
{
	gateA = v;
	invalidateGeometry();
}

void TwoGateNode::setGateB(const double2 & v)
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
	
	if (symbol) {
		Path * p = symbol->generateGeometry();
		double2 m = double2((gateA.x + gateB.x) / 2, (gateA.y + gateB.y) / 2);
		for (int i = 0; i < p->nodes.size(); i++) {
			double2 & v = p->nodes[i].p;
			v.x += m.x;
			v.y += m.y;
		}
		l->paths.insert(p);
		std::cout << "got path " << (void *)p << std::endl;
	}
	
	geometry.layers[0] = l;
	Node::generateGeometry();
}
