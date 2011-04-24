#include "symbol.h"
#include <iostream>


void Symbol::bindToLua(lua_State * L)
{
	using namespace luabind;
	module(L)
	[
		class_<Symbol, Symbol::ptr>("Symbol")
			.def(constructor<>())
			//.def_readwrite("nodes", &Symbol::nodes)
			.def("addNode", &Symbol::addNode)
			//.def_readwrite("paths", &Symbol::paths)
			.def("addPath", &Symbol::addPath)
			.def_readwrite("strokes", &Symbol::strokes),
		
		class_<Node>("Node")
			.def(constructor<>())
			.def_readwrite("x", &Node::x)
			.def_readwrite("y", &Node::y),
		
		class_<Path>("Path")
			.def(constructor<>())
			.def_readwrite("nodes", &Path::nodes)
			.def_readwrite("closed", &Path::closed),
		
		class_<Stroke>("Stroke")
			.def(constructor<>())
			.def_readwrite("path", &Stroke::path)
			.def_readwrite("layer", &Stroke::layer),
		
		class_<std::vector<Stroke> >("Stroke_vector")
			.def("push_back", &std::vector<Stroke>::push_back)
			.def("at", (Stroke&(std::vector<Stroke>::*)(size_t))&std::vector<Stroke>::operator[]),
		
		class_<std::vector<std::string> >("string_vector")
			.def("push_back", &std::vector<std::string>::push_back)
			.def("at", (std::string&(std::vector<std::string>::*)(size_t))&std::vector<std::string>::operator[])
	];
}

void Symbol::draw(Cairo::RefPtr<Cairo::Context>& cr)
{
	for (std::vector<Stroke>::iterator strk = strokes.begin(); strk != strokes.end(); strk++) {
		cr->save();
		bool first = true;
		std::cout << "drawing stroke with path " << (*strk).path << std::endl;
		const Path & path = paths[(*strk).path];
		for (std::vector<std::string>::const_iterator nds = path.nodes.begin(); nds != path.nodes.end(); nds++) {
			const Node & node = nodes[*nds];
			std::cout << "   node " << node.x << ", " << node.y << std::endl;
			if (first)
				cr->move_to(node.x, node.y);
			else
				cr->line_to(node.x, node.y);
			first = false;
		}
		if (path.closed)
			cr->close_path();
		cr->stroke();
		cr->restore();
	}
}

