#include <gtkmm.h>

#include "symbol/manager.h"
#include <iostream>


int main(int argc, char * argv[])
{
	Gtk::Main kit(argc, argv);
	
	Gtk::Window window;
	
	Symbol::Arguments args;
	args["standard"] = "ansi";
	
	Symbol::ptr r1 = SymbolManager::getSingleton()->getSymbol("resistor");
	std::cout << "r1 = " << r1 << std::endl;
	Symbol::ptr r2 = SymbolManager::getSingleton()->getSymbol("resistor");
	std::cout << "r2 = " << r2 << std::endl;
	Symbol::ptr r3 = SymbolManager::getSingleton()->getSymbol("resistor", args);
	std::cout << "r3 = " << r3 << std::endl;
	
	Gtk::Main::run(window);
	
	return 0;
}
