#include "CircuitEditor.h"


CircuitEditor::CircuitEditor()
{
	add(editor);
	editor.show();
	set_title("Circuit Editor - Voltam");
	resize(800, 600);
}

CircuitEditor::~CircuitEditor()
{
}
