#pragma once
#include <gtkmm/window.h>
#include "CircuitEditorWidget.h"

class CircuitEditor : public Gtk::Window
{
public:
	CircuitEditor();
	virtual ~CircuitEditor();

protected:
	CircuitEditorWidget editor;
};
