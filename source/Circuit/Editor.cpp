#include "Editor.h"
using namespace Circuit;


Editor::Editor()
{
	add(editor);
	editor.show();
	set_title("Circuit Editor - Voltam");
	resize(800, 600);
}

Editor::~Editor()
{
}
