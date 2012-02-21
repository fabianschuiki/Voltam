#include "Node.h"
using namespace Circuit;


Node::Node()
{
	geometry_valid = false;
}

Geometry::Geometry & Node::getGeometry()
{
	if (!geometry_valid)
		generateGeometry();
	return geometry;
}

void Node::invalidateGeometry()
{
	geometry_valid = false;
	geometry.layers.clear();
}
