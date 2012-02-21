#include <gtkmm.h>

#include "Circuit/Editor.h"


int main(int argc, char * argv[])
{
	Gtk::Main kit(argc, argv);
	
	Circuit::Editor editor;
	
	Gtk::Main::run(editor);
	
	return 0;
}
