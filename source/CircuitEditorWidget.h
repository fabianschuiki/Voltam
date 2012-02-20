#pragma once
#include <gtkmm/drawingarea.h>


class CircuitEditorWidget : public Gtk::DrawingArea
{
public:
	CircuitEditorWidget();
	virtual ~CircuitEditorWidget();

protected:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
};
