#include <gtkmm.h>

#include "symbol/manager.h"
#include <iostream>


static Symbol::ptr resistor = Symbol::ptr();
static Gtk::DrawingArea * area = NULL;

bool on_expose(GdkEventExpose * event)
{
	Glib::RefPtr<Gdk::Window> window = area->get_window();
	if (window) {
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		cr->set_antialias(Cairo::ANTIALIAS_NONE);
		
		cr->scale(20, 20);
		cr->translate(5, 5);
		cr->set_line_width(0.1);
		
		cr->save();
		cr->set_source_rgba(1, 1, 1, 1);
		cr->paint();
		
		cr->set_source_rgba(0.5, 0, 0, 1);
		if (resistor)
			resistor->draw(cr);
		cr->restore();
	}
	return true;
}

int main(int argc, char * argv[])
{
	Gtk::Main kit(argc, argv);
	
	Gtk::Window window;
	
	area = new Gtk::DrawingArea;
	area->signal_expose_event().connect(sigc::ptr_fun(&on_expose));
	window.add(*area);
	area->show();
	
	Symbol::Arguments args;
	args["standard"] = "ansi";
	
	Symbol::ptr r1 = SymbolManager::getSingleton()->getSymbol("resistor");
	std::cout << "r1 = " << r1 << std::endl;
	Symbol::ptr r2 = SymbolManager::getSingleton()->getSymbol("resistor");
	std::cout << "r2 = " << r2 << std::endl;
	Symbol::ptr r3 = SymbolManager::getSingleton()->getSymbol("resistor", args);
	std::cout << "r3 = " << r3 << std::endl;
	
	resistor = SymbolManager::getSingleton()->getSymbol("resistor");
	if (resistor) {
		for (std::map<std::string, Symbol::Path>::iterator it = resistor->paths.begin(); it != resistor->paths.end(); it++)
			std::cout << "path " << it->first << std::endl;
		for (std::map<std::string, Symbol::Node>::iterator it = resistor->nodes.begin(); it != resistor->nodes.end(); it++)
			std::cout << "node " << it->first << " " << (it->second).x << ", " << (it->second).y << std::endl;
	}
	
	Gtk::Main::run(window);
	
	return 0;
}

