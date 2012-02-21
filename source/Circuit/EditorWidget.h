#pragma once

#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <set>

#include "../Geometry/Geometry.h"
#include "../lib/Library.h"
#include "Node.h"


namespace Circuit
{
	class EditorWidget : public Gtk::DrawingArea
	{
		public:
			EditorWidget();
			virtual ~EditorWidget();
			
			typedef std::set<Geometry::Geometry *> GeometrySet;
			GeometrySet geometries;

			typedef std::set<Node *> NodeSet;
			NodeSet nodes;

			lib::Library lib;
			
		protected:
			virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	};
}
