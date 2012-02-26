#pragma once
#include <gc_cpp.h>
#include <gdkmm/color.h>
#include <string>
#include "Path.h"

namespace Geometry
{
	class Layer : public gc
	{
	public:
		typedef std::vector<Layer *> Vector;
		
		std::string name;
		Gdk::Color color;
		Path::Set paths;
	};
}
