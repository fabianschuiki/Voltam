#include "generator.h"

#include <iostream>

	
SymbolGenerator::SymbolGenerator(std::string name) : name(name)
{
}



const Symbol::ptr & SymbolGenerator::generateSymbol()
{
	return generateSymbol("");
}

const Symbol::ptr & SymbolGenerator::generateSymbol(std::string arguments)
{
	//TODO: generate symbol!
	std::cout << "I (" << name << ") have been asked to generate a symbol with arguments «" << arguments << "»" << std::endl;
	return Symbol::ptr();
}

