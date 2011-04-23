#pragma once

#include <string>

#include "symbol.h"


class SymbolGenerator {

	const std::string name;
	
public:
	typedef boost::shared_ptr<SymbolGenerator> ptr;
	
	SymbolGenerator(std::string name);
	
	const Symbol::ptr & generateSymbol();
	const Symbol::ptr & generateSymbol(std::string arguments);
};

