#pragma once

#include <map>
#include <string>

#include "generator.h"


class SymbolGeneratorManager {

	typedef std::map< std::string, SymbolGenerator::ptr > NamedGenerator;

	NamedGenerator store;
	
public:
	static SymbolGeneratorManager * getSingleton();
	
	const SymbolGenerator::ptr & getGenerator(std::string name);
	
	Symbol::ptr generateSymbol(std::string name);
	Symbol::ptr generateSymbol(std::string name, std::string arguments);
};

