#include "generatormanager.h"


SymbolGeneratorManager * SymbolGeneratorManager::getSingleton()
{
	static SymbolGeneratorManager instance;
	return &instance;
}



const SymbolGenerator::ptr & SymbolGeneratorManager::getGenerator(std::string name)
{
	//Create the generator if required.
	if (!store.count(name))
		store[name] = SymbolGenerator::ptr(new SymbolGenerator(name));
	
	return store[name];
}



Symbol::ptr SymbolGeneratorManager::generateSymbol(std::string name)
{
	return generateSymbol(name, Symbol::Arguments());
}

Symbol::ptr SymbolGeneratorManager::generateSymbol(std::string name, Symbol::Arguments arguments)
{
	//Try to find the appropriate generator for this symbol.
	SymbolGenerator::ptr generator = getGenerator(name);
	if (!generator)
		return Symbol::ptr(); //TODO: throw exception
	
	return generator->generateSymbol(arguments);
}

