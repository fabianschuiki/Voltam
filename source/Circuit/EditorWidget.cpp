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
	add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::BUTTON_MOTION_MASK);
	
	//Default layers.
	Layer * l;
	l = new Layer;
	l->name = "symbol";
	l->color.set_hsv(330, 1, 0.5);
	layers.push_back(l);
	
	//DEBUG: nodes
	TwoGateNode * n = new TwoGateNode;
	n->symbol = lib.symbolsByName["resistor"];
	n->setGateA(double2(200, 200));
	n->setGateB(double2(200, 300));
	nodes.insert(n);
	
	updateLayers();
}

EditorWidget::~EditorWidget()
{
}

/** Compiles the geometry from all nodes down to one set of layers. */
void EditorWidget::updateLayers()
{
	for (Layer::Vector::iterator il = layers.begin(); il != layers.end(); il++) {
		Layer * l = *il;
		l->paths.clear();
		for (NodeSet::iterator in = nodes.begin(); in != nodes.end(); in++) {
			Node * n = *in;
			Path::Set & np = n->getLayers()[l->name];
			l->paths.insert(np.begin(), np.end());
		}
	}
	queue_draw();
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
	for (Layer::Vector::iterator il = layers.begin(); il != layers.end(); il++) {
		Layer * l = *il;
		cr->save();
		cr->set_source_rgb(l->color.get_red_p(), l->color.get_green_p(), l->color.get_blue_p());
		for (Path::Set::iterator ip = l->paths.begin(); ip != l->paths.end(); ip++) {
			Path * p = *ip;
			for (int i = 0; i < p->nodes.size(); i++) {
				const Path::Node & n = p->nodes[i];
				if (n.move)
					cr->move_to(n.p.x, n.p.y);
				else
					cr->line_to(n.p.x, n.p.y);
			}
			if (p->close)  cr->close_path();
			if (p->fill)   cr->fill();
			if (p->stroke) cr->stroke();
		}
		cr->restore();
	}
	
	return true;
}

bool EditorWidget::on_button_press_event(GdkEventButton * ev)
{
	isDragging = true;
	dragCurrentPoint = int2(ev->x, ev->y);
	dragStartPoint = dragCurrentPoint;
	on_drag(DragStart);
	return true;
}

bool EditorWidget::on_button_release_event(GdkEventButton * ev)
{
	dragCurrentPoint = int2(ev->x, ev->y);
	dragEndPoint = dragCurrentPoint;
	on_drag(DragDone);
	isDragging = false;
	return true;
}

bool EditorWidget::on_motion_notify_event(GdkEventMotion * ev)
{
	if (isDragging) {
		dragCurrentPoint = int2(ev->x, ev->y);
		on_drag(DragUpdate);
	}
	return true;
}

void EditorWidget::on_drag(DragState state)
{
	int2 gridStart   = dragStartPoint   / 20;
	int2 gridCurrent = dragCurrentPoint / 20;
	int2 gridEnd     = dragEndPoint     / 20;
	gridStart   *= 20;
	gridCurrent *= 20;
	gridEnd     *= 20;
	
	switch (state) {
		case DragStart: {
			draggingNode = new TwoGateNode;
			draggingNode->symbol = lib.symbolsByName["resistor"];
			draggingNode->setGateA(gridStart);
			draggingNode->setGateB(gridCurrent);
			nodes.insert(draggingNode);
			updateLayers();
		} break;
		case DragUpdate: {
			draggingNode->setGateB(gridCurrent);
			updateLayers();
		} break;
		case DragDone: {
			draggingNode->setGateB(gridEnd);
			draggingNode = NULL;
			updateLayers();
		} break;
	}
}
