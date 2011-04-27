#include <gtkmm.h>

//#include "symbol/manager.h"
#include <iostream>
#include "geometry/bezierpath.h"

using namespace Voltam;


//static Symbol::ptr resistor = Symbol::ptr();
static Gtk::DrawingArea * area = NULL;
static Voltam::Geometry::BezierPath path;

bool on_expose(GdkEventExpose * event)
{
	Glib::RefPtr<Gdk::Window> window = area->get_window();
	if (window) {
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		//cr->set_antialias(Cairo::ANTIALIAS_NONE);
		cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
		cr->set_line_join(Cairo::LINE_JOIN_BEVEL);
		
		cr->scale(20, 20);
		cr->translate(3, 3);
		cr->set_line_width(0.1);
		
		cr->save();
		cr->set_source_rgba(1, 1, 1, 1);
		cr->paint();
		
		cr->set_source_rgba(0.5, 0, 0, 1);
		path.execute(cr);
		cr->stroke();
		cr->restore();
	}
	return true;
}

int main(int argc, char * argv[])
{
	Gtk::Main kit(argc, argv);
	
	Gtk::Window window;
	window.set_title("Voltam Development");
	window.resize(800, 600);
	
	area = new Gtk::DrawingArea;
	area->signal_expose_event().connect(sigc::ptr_fun(&on_expose));
	window.add(*area);
	area->show();
	
	/*path.moveTo(double2(-1,  0.25));
	path.lineTo(double2( 1,  0.25));
	path.lineTo(double2( 1, -0.25));
	path.lineTo(double2(-1, -0.25));
	path.close();*/
	/*path.rect(-1, -0.5, 2, 1);
	path.moveTo(-1, 0); path.lineTo(-2, 0);
	path.moveTo( 1, 0); path.lineTo( 2, 0);*/
	
	path.moveTo(-0.5, 0);
	path.lineTo(0.5, 0.5);
	path.lineTo(0.5, -0.5);
	path.close();
	path.moveTo(-0.5, -0.5);
	path.lineTo(-0.5, 0.5);
	path.moveTo(-0.5, 0);
	path.lineTo(-1.5, 0);
	path.moveTo(0.5, 0);
	path.lineTo(1.5, 0);
	
	/*Symbol::Arguments args;
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
	}*/
	
	Gtk::Main::run(window);
	
	return 0;
}

