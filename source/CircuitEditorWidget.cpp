#include <cairomm/context.h>
#include "CircuitEditorWidget.h"


CircuitEditorWidget::CircuitEditorWidget()
{
}

CircuitEditorWidget::~CircuitEditorWidget()
{
}

bool CircuitEditorWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int w = allocation.get_width();
	const int h = allocation.get_height();
	
	//Draw the background.
	cr->save();
	cr->set_source_rgba(1, 1, 1, 1);
	cr->paint();
	cr->set_source_rgba(0.9, 0.9, 0.9, 1);
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
	
	return true;
}
