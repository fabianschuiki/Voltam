#pragma once

#include <gtkmm.h>
#include <boost/smart_ptr.hpp>
#include <luabind/luabind.hpp>


class Symbol {
public:
	typedef boost::shared_ptr<Symbol> ptr;
	typedef std::map<std::string, std::string> Arguments;
	
	static void bindToLua(lua_State * L);
	
	class Node {
	public:
		double x;
		double y;
	};
	std::map<std::string, Node> nodes;
	void addNode(std::string k, const Node & v) { nodes[k] = v; }
	
	class Path {
	public:
		std::vector<std::string> nodes;
		bool closed;
	};
	std::map<std::string, Path> paths;
	void addPath(std::string k, const Path & v) { paths[k] = v; }
	
	class Stroke {
	public:
		std::string path;
		int layer;
	};
	std::vector<Stroke> strokes;
	
	void draw(Cairo::RefPtr<Cairo::Context>& cr);
};

