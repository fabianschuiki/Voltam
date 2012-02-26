#include "Node.h"

using namespace Circuit;


Node::Node()
{
	valid = false;
}

Node::Layers & Node::getLayers()
{
	if (!valid)
		update();
	return layers;
}

void Node::invalidate()
{
	layers.clear();
	valid = false;
}
