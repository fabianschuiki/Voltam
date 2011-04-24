#pragma once

#include <map>
#include <string>
#include <vector>

#include "symbol.h"


class SymbolManager {
	
	typedef std::map< Symbol::Arguments, Symbol::ptr > AttributedSymbol;
	typedef std::map< std::string, AttributedSymbol > NamedAttributedSymbol;
	
	NamedAttributedSymbol store;
	
public:
	static SymbolManager * getSingleton();
	
	const Symbol::ptr & getSymbol(std::string name);
	const Symbol::ptr & getSymbol(std::string name, Symbol::Arguments arguments);
};

