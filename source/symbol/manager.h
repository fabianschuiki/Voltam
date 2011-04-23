#pragma once

#include <map>
#include <string>
#include <vector>

#include "symbol.h"


class SymbolManager {
	
	typedef std::map< std::string, Symbol::ptr > AttributedSymbol;
	typedef std::map< std::string, AttributedSymbol > NamedAttributedSymbol;
	
	NamedAttributedSymbol store;
	
public:
	static SymbolManager * getSingleton();
	
	const Symbol::ptr & getSymbol(std::string name);
	const Symbol::ptr & getSymbol(std::string name, std::string arguments);
};

