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
	
	//DEBUG: nodes
	TwoGateNode * n = new TwoGateNode;
	n->symbol = lib.symbolsByName["resistor"];
	n->setGateA(double2(200, 200));
	n->setGateB(double2(200, 320));
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
	for (int x = 0; x < w; x += 15) {
		cr->move_to(x+0.5, 0);
		cr->line_to(x+0.5, h);
	}
	for (int y = 0; y < h; y += 15) {
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
			cr->close_path();
			if ((*p)->fill)
				cr->fill();
			else
				cr->stroke();
		}
	}
	cr->restore();
	
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
	std::cout << "on_drag " << state << std::endl;
	if (state == DragDone) {
		TwoGateNode * n = new TwoGateNode;
		n->symbol = lib.symbolsByName["resistor"];
		n->setGateA(dragStartPoint);
		n->setGateB(dragEndPoint);
		nodes.insert(n);
	}
}
