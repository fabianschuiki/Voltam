#pragma once


class Component {
	boost::smart_ptr<Device> device;
	
	//Supplied by device
	boost::smart_ptr<Symbol> symbol;
	boost::smart_ptr<Package> package;
};

