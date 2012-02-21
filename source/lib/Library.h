#pragma once
#include <objlua/objlua.h>
#include <set>
#include <string>

namespace lib
{
	class Symbol;

	class Library
	{
	public:
		Library();
		
	protected:
		LuaState L;
		
		typedef std::set<Symbol *> SymbolSet;
		SymbolSet symbols;
		void loadSymbol(const char * path);
	};
}
