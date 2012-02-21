#pragma once
#include <gtkmm/window.h>
#include "EditorWidget.h"

namespace Circuit
{
	class Editor : public Gtk::Window
	{
	public:
		Editor();
		virtual ~Editor();

	protected:
		EditorWidget editor;
	};
}
