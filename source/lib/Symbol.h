#pragma once
#include <objlua/objlua.h>
#include "../Geometry/Geometry.h"
#include "SymbolTerminal.h"

namespace lib
{
	class Library;
	
	class Symbol
	{
	public:
		LuaState & L;
		Symbol(LuaState & L, int index = -1);
		
		void init();
		bool isValid() const;
		
		const std::string & getName() const { return name; }
		
		void update();
		Geometry::Geometry geometry;
		SymbolTerminal::Set terminals;
		Geometry::Path::Vector paths;
		
		//deprecated
		Geometry::Path * generateGeometry();
		
	protected:
		int ref;
		
		std::string name;
	};
}
