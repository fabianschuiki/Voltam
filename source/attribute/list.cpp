#include "list.h"
#include <sstream>

using namespace Voltam;
using namespace Voltam::Attribute;


List::List() {}
List::List(const List & l) { *this = l; }
List::List(const List * l) { *this = *l; }



List::List & List::operator=(const List & l)
{
	attributes = l.attributes;
	return *this;
}



bool List::set(const std::string & name, IAttribute * attribute, bool replace)
{
	if (replace || !has(name)) {
		attributes[name] = attribute;
		return true;
	}
	return false;
}

SmartPointer<IAttribute> & List::get(const std::string & name)
{
	return attributes[name];
}

bool List::has(const std::string & name) const
{
	return attributes.count(name);
}

void List::merge(const List & other, bool replace)
{
	for (Attributes::const_iterator it = other.attributes.begin();
		 it != other.attributes.end(); it++)
		set(it->first, it->second, replace);
}



SmartPointer<IAttribute> & List::operator[](const std::string & name)
{
	return get(name);
}

List List::operator+(const List & other)
{
	List l(*this);
	l.merge(other);
	return l;
}

List & List::operator+=(const List & other)
{
	merge(other);
	return *this;
}



List::iterator List::begin()				{ return attributes.begin(); }
List::iterator List::end()					{ return attributes.end(); }
List::const_iterator List::begin() const	{ return attributes.begin(); }
List::const_iterator List::end() const		{ return attributes.end(); }

List::reverse_iterator List::rbegin()				{ return attributes.rbegin(); }
List::reverse_iterator List::rend()					{ return attributes.rend(); }
List::const_reverse_iterator List::rbegin() const	{ return attributes.rbegin(); }
List::const_reverse_iterator List::rend() const		{ return attributes.rend(); }



List::operator std::string() const
{
	std::stringstream s;
	s << "{\n";
	for (const_iterator it = begin(); it != end(); it++)
		s << "\t" << it->first << " = " << (std::string)*(it->second) << "\n";
	s << "}";
	return s.str();
}
