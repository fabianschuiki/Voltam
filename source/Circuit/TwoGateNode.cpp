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
	LOG(DEBUG, "updating geometry");
	
	Layer * l = new Layer;
	geometry.layers[0] = l;
	
	//Calculate the translation for the original symbol geometry.
	double2 center = (gateA + gateB) / 2;
	double2 unitX  = (gateB - gateA).unit() * 10;
	double2 unitY(unitX.y, -unitX.x);
	
	LOG(DEBUG, "coords: %s x %s", unitX.description().c_str(), unitY.description().c_str());
	
	//Draw debugging things.
	/*Path * center_path = new Path;
	center_path->nodes.push_back((Path::Node){center-double2(5, 0), true});
	center_path->nodes.push_back((Path::Node){center+double2(5, 0), false});
	center_path->nodes.push_back((Path::Node){center-double2(0, 5), true});
	center_path->nodes.push_back((Path::Node){center+double2(0, 5), false});
	l->paths.insert(center_path);*/
	
	/*Path * coords_path = new Path;
	coords_path->nodes.push_back((Path::Node){center, true});
	coords_path->nodes.push_back((Path::Node){center+unitX*30, false});
	coords_path->nodes.push_back((Path::Node){center, true});
	coords_path->nodes.push_back((Path::Node){center+unitY*30, false});
	l->paths.insert(coords_path);*/
	
	//Translate the symbol paths.
	for (Path::Vector::iterator ip = symbol->paths.begin(); ip != symbol->paths.end(); ip++) {
		Path * p = new Path(**ip);
		for (int i = 0; i < p->nodes.size(); i++) {
			double2 & v = p->nodes[i].p;
			v = unitX * v.x + unitY * v.y + center;
		}
		l->paths.insert(p);
	}
	
	//Draw the terminals.
	Path * terms = new Path;
	for (lib::SymbolTerminal::Set::iterator it = symbol->terminals.begin(); it != symbol->terminals.end(); it++) {
		terms->nodes.push_back((Path::Node){(unitX * (*it)->pos.x + unitY * (*it)->pos.y + center), true});
		terms->nodes.push_back((Path::Node){(*it)->name == "a" ? gateA : gateB, false});
	}
	l->paths.insert(terms);
	
	/*cout << "generating geometry" << endl;
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
	
	geometry.layers[0] = l;*/
	Node::generateGeometry();
}
