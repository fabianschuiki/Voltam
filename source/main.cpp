#include <gtkmm.h>

#include "symbol/manager.h"
#include <iostream>


int main(int argc, char * argv[])
{
	Gtk::Main kit(argc, argv);
	
	Gtk::Window window;
	
	Symbol::ptr r1 = SymbolManager::getSingleton()->getSymbol("resistor");
	std::cout << "r1 = " << r1 << std::endl;
	
	Gtk::Main::run(window);
	
	return 0;
}
