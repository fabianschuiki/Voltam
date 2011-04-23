#include "manager.h"
#include "generatormanager.h"


SymbolManager * SymbolManager::getSingleton()
{
	static SymbolManager instance;
	return &instance;
}



const Symbol::ptr & SymbolManager::getSymbol(std::string name)
{
	return getSymbol(name, "");
}

const Symbol::ptr & SymbolManager::getSymbol(std::string name, std::string arguments)
{
	//Create the symbol if required.
	if (!store.count(name) || !store[name].count(arguments))
		store[name][arguments] = SymbolGeneratorManager::getSingleton()->generateSymbol(name, arguments);
	
	return store[name][arguments];
}

