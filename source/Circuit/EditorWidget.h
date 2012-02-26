#pragma once

#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <set>

#include "../Geometry/Geometry.h"
#include "../lib/Library.h"
#include "../math/Vector2D.h"
#include "Node.h"
#include "TwoGateNode.h"


namespace Circuit
{
	class EditorWidget : public Gtk::DrawingArea
	{
	public:
		EditorWidget();
		virtual ~EditorWidget();

		typedef std::set<Node *> NodeSet;
		NodeSet nodes;

		lib::Library lib;
		
	protected:
		Geometry::Layer::Vector layers;
		void updateLayers();
		
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
		
		virtual bool on_button_press_event(GdkEventButton * ev);
		virtual bool on_button_release_event(GdkEventButton * ev);
		virtual bool on_motion_notify_event(GdkEventMotion * ev);
		
		bool isDragging;
		int2 dragStartPoint;
		int2 dragCurrentPoint;
		int2 dragEndPoint;
		typedef enum {
			DragStart,
			DragUpdate,
			DragDone,
			DragCancel
		} DragState;
		void on_drag(DragState state);
		
		TwoGateNode * draggingNode;
	};
}
