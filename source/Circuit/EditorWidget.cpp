#include <cairomm/context.h>
#include <iostream>
#include "EditorWidget.h"
#include "TwoGateNode.h"

using namespace Circuit;
using Geometry::Path;
using Geometry::Layer;
using Geometry::Geometry;


EditorWidget::EditorWidget()
{
	//DEBUG: geometries
	Path * p = new Path;
	p->nodes.push_back((Path::Node){Vector( 0,  0), true});
	p->nodes.push_back((Path::Node){Vector(50, 50), false});
	p->nodes.push_back((Path::Node){Vector( 0, 50), false});

	Layer * l = new Layer;
	l->paths.insert(p);
	
	Geometry::Geometry * g = new Geometry::Geometry;
	g->layers[0] = l;

	geometries.insert(g);

	//DEBUG: nodes
	TwoGateNode * n = new TwoGateNode;
	n->setGateA(Vector(200, 200));
	n->setGateB(Vector(200, 300));
	nodes.insert(n);
}

EditorWidget::~EditorWidget()
{
}


bool EditorWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int w = allocation.get_width();
	const int h = allocation.get_height();
	
	//Draw the background.
	cr->save();
	cr->set_source_rgb(1, 1, 1);
	cr->paint();
	cr->set_source_rgb(0.9, 0.9, 0.9);
	cr->set_line_width(1);
	for (int x = 0; x < w; x += 20) {
		cr->move_to(x+0.5, 0);
		cr->line_to(x+0.5, h);
	}
	for (int y = 0; y < h; y += 20) {
		cr->move_to(0, y+0.5);
		cr->line_to(w, y+0.5);
	}
	cr->stroke();
	cr->restore();

	//Draw the layers.
	//TODO: draw other layers than layer 0
	cr->save();
	cr->set_source_rgba(0.5, 0, 0.25, 1);
	for (NodeSet::iterator n = nodes.begin(); n != nodes.end(); n++) {
		Layer * l = (*n)->getGeometry().layers[0];
		if (!l) continue;
		
		for (Layer::PathSet::iterator p = l->paths.begin(); p != l->paths.end(); p++) {
			for (int i = 0; i < (*p)->nodes.size(); i++) {
				const Path::Node & n = (*p)->nodes[i];
				if (n.move)
					cr->move_to(n.p.x, n.p.y);
				else
					cr->line_to(n.p.x, n.p.y);
			}
			if ((*p)->fill)
				cr->fill();
			else
				cr->stroke();
		}
	}
	cr->stroke();
	cr->restore();
	
	return true;
}
