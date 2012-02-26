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
		SymbolTerminal::Set terminals;
		Geometry::Path::Set paths;
		
	protected:
		int ref;
		
		std::string name;
	};
}
