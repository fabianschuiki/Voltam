#include <gtkmm.h>

//#include "symbol/manager.h"
#include <iostream>
#include "geometry/bezierpath/invocation.h"
#include "smartpointer.h"
#include "library/symbol/symbol.h"

using namespace Voltam;


//static Symbol::ptr resistor = Symbol::ptr();
static Gtk::DrawingArea * area = NULL;
static SmartPointer<Library::Symbol> symbol;

bool on_expose(GdkEventExpose * event)
{
	Glib::RefPtr<Gdk::Window> window = area->get_window();
	if (window) {
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		//cr->set_antialias(Cairo::ANTIALIAS_NONE);
		cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
		cr->set_line_join(Cairo::LINE_JOIN_BEVEL);
		
		cr->scale(20, 20);
		cr->translate(10, 10);
		
		cr->save();
		cr->set_source_rgba(1, 1, 1, 1);
		cr->paint();
		
		if (symbol) {
			cr->select_font_face("Ubuntu", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
			cr->set_font_size(0.5);
			
			//Draw the symbol
			cr->save();
			cr->set_source_rgba(0.5, 0, 0, 1);
			cr->set_line_width(2 / 20.0);
			for (Library::Symbol::PathInvocations::const_iterator it = symbol->pathInvocations.begin(); it != symbol->pathInvocations.end(); it++)
				(*it)->draw(cr);
			cr->restore();
				
			//Draw the terminals
			cr->set_line_width(1 / 20.0);
			cr->translate(0.5 / 20.0, 0.5 / 20.0);
			for (Library::Symbol::Terminals::const_iterator it = symbol->terminals.begin(); it != symbol->terminals.end(); it++) {
				cr->set_source_rgba(0.5, 0, 0, 1);
				Geometry::BezierPath p;
				p.moveTo((*it)->root);
				p.lineTo((*it)->tip);
				p.execute(cr);
				cr->stroke();
				
				cr->set_source_rgba(0.75, 0.75, 0.75, 1);
				const std::string & n = (*it)->signals.back()->name;
				Cairo::TextExtents extents;
				cr->get_text_extents(n, extents);
				cr->move_to((*it)->tip.x - extents.width/2, (*it)->tip.y - 0.1);
				cr->show_text(n);
			}
		}
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
	
	const bool schottky = true;
	const bool zener = true;
	
	symbol = new Library::Symbol();
	Geometry::BezierPath * path;
	
	path = new Geometry::BezierPath();
	path->moveTo(-0.5, 0);
	path->lineTo(0.5, 0.5);
	path->lineTo(0.5, -0.5);
	path->close();
	symbol->pathInvocations.push_back(new Geometry::BezierPath::Invocation(path, true, true));
	
	path = new Geometry::BezierPath();	
	if (schottky) {
		path->moveTo(-0.8, 0.4);
		path->lineTo(-0.8, 0.6);
		path->lineTo(-0.5, 0.6);
	} else {
		path->moveTo(-0.5, 0.6);
	}
	path->lineTo(-0.5, -0.6);
	if (zener || schottky) path->lineTo(-0.2, -0.6);
	if (schottky) path->lineTo(-0.2, -0.4);
	symbol->pathInvocations.push_back(new Geometry::BezierPath::Invocation(path, true, false));
	
	
	Library::Symbol::Terminal * anodeTerminal = new Library::Symbol::Terminal();
	anodeTerminal->root = double2(0.5, 0);
	anodeTerminal->tip  = double2(2, 0);
	Library::Symbol::Signal * anodeSignal = new Library::Symbol::Signal();
	anodeSignal->name = "A";
	anodeTerminal->signals.push_back(anodeSignal);
	symbol->terminals.push_back(anodeTerminal);
	
	Library::Symbol::Terminal * cathodeTerminal = new Library::Symbol::Terminal();
	cathodeTerminal->root = double2(-0.5, 0);
	cathodeTerminal->tip  = double2(-2, 0);
	Library::Symbol::Signal * cathodeSignal = new Library::Symbol::Signal();
	cathodeSignal->name = "C";
	cathodeTerminal->signals.push_back(cathodeSignal);
	symbol->terminals.push_back(cathodeTerminal);
	
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

