#include <gtkmm.h>

#include "CircuitEditor.h"


int main(int argc, char * argv[])
{
	Gtk::Main kit(argc, argv);
	
	CircuitEditor editor;
	
	Gtk::Main::run(editor);
	
	return 0;
}
