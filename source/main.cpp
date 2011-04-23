#include <gtkmm.h>

#include "symbol/manager.h"


int main(int argc, char * argv[])
{
	Gtk::Main kit(argc, argv);
	
	Gtk::Window window;
	
	Symbol::ptr r1 = SymbolManager::getSingleton()->getSymbol("resistor");
	
	Gtk::Main::run(window);
	
	return 0;
}
