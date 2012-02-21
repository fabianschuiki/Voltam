#pragma once
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <set>
#include "../Geometry/Geometry.h"


namespace Circuit
{
	class EditorWidget : public Gtk::DrawingArea
	{
		public:
			EditorWidget();
			virtual ~EditorWidget();
			
			typedef std::set<Geometry::Geometry *> GeometrySet;
			GeometrySet geometries;
			
		protected:
			virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	};
}
