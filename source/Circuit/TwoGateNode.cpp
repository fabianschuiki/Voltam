#include "TwoGateNode.h"

#include <iostream>
using namespace std;

using namespace Circuit;
using Geometry::Path;
using Geometry::Layer;


void TwoGateNode::setGateA(const double2 & v)
{
	gateA = v;
	invalidate();
}

void TwoGateNode::setGateB(const double2 & v)
{
	gateB = v;
	invalidate();
}

void TwoGateNode::update()
{
	LOG(DEBUG, "updating");
	
	layers.clear();
	Path::Set & symbolPaths = layers["symbol"];
	
	//Calculate the translation for the original symbol geometry.
	double2 center = (gateA + gateB) / 2;
	double2 unitX  = (gateB - gateA).unit() * 10;
	double2 unitY(unitX.y, -unitX.x);
	
	LOG(DEBUG, "coords: %s x %s", unitX.description().c_str(), unitY.description().c_str());
	
	//Translate the symbol paths.
	for (Path::Set::iterator ip = symbol->paths.begin(); ip != symbol->paths.end(); ip++) {
		Path * p = new Path(**ip);
		for (int i = 0; i < p->nodes.size(); i++) {
			double2 & v = p->nodes[i].p;
			v = unitX * v.x + unitY * v.y + center;
		}
		symbolPaths.insert(p);
	}
	
	//Draw the terminals.
	Path * terms = new Path;
	for (lib::SymbolTerminal::Set::iterator it = symbol->terminals.begin(); it != symbol->terminals.end(); it++) {
		terms->nodes.push_back((Path::Node){(unitX * (*it)->pos.x + unitY * (*it)->pos.y + center), true});
		terms->nodes.push_back((Path::Node){(*it)->name == "a" ? gateA : gateB, false});
	}
	symbolPaths.insert(terms);
	
	valid = true;
}
