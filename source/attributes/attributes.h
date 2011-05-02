#pragma once

#include <map>
#include <string>
#include "attribute.h"


class Attributes {
	
	std::map< std::string, SmartPointer<IAttribute> > attributes;
	
public:
	void set(const std::string & name, IAttribute * attribute);
	bool has(const std::string & name) const;
	IAttribute * get(const std::string & name) const;
	IAttribute * operator[](const std::string & name);
	
	void merge(const Attributes & other);
	Attributes operator+(const Attributes & other);
	Attributes & operator+=(const Attributes & other);
};
