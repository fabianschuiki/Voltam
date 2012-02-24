#pragma once
#include <map>
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
		
		typedef std::map<std::string, Symbol *> SymbolMap;
		SymbolMap symbolsByName;
		
	protected:
		LuaState L;
		
		typedef std::set<Symbol *> SymbolSet;
		SymbolSet symbols;
		void loadSymbol(const char * path);
	};
}
