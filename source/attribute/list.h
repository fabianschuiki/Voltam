#pragma once

#include <map>
#include <string>
#include "../misc/smartpointer.h"
#include "attribute.h"


namespace Voltam {
	namespace Attribute {
		
		/**
		 * Attribute::List
		 *
		 * The attribute list manages a set of attributes of various data types. Multiple lists may
		 * be merged together.
		 */
		class List {
		public:
			
			//Convenience typedef for the attribute map and its iterators.
			typedef std::map< std::string, SmartPointer<IAttribute> > Attributes;
			typedef Attributes::iterator iterator;
			typedef Attributes::const_iterator const_iterator;
			typedef Attributes::reverse_iterator reverse_iterator;
			typedef Attributes::const_reverse_iterator const_reverse_iterator;
			
		private:
			
			//Map associating an attribute with a string.
			Attributes attributes;
			
		public:
			
			//Construction.
			List();
			List(const List & l);
			List(const List * l);
			
			//Assignment.
			List & operator=(const List & l);
			
			//Stores the given attribute under the given name. If replace is set to true, any
			//existing attributes with this name will be replaced by the new one. Returns whether
			//the attribute was added or not.
			bool set(const std::string & name, IAttribute * attribute, bool replace = true);
			
			//Returns the attribute stored under the given name, or NULL if there is none.
			SmartPointer<IAttribute> & get(const std::string & name);
			
			//Returns whether there is an attribute stored under the given name.
			bool has(const std::string & name) const;
			
			//Merges the given attribute list into this one. If replace is true, the attribtues in
			//the other list will replaced all attributes of the same name in this list.
			void merge(const List & other, bool replace = true);
			
			//Convenience attribute access.
			SmartPointer<IAttribute> & operator[](const std::string & name);
			
			//Convenience replacement merge.
			List operator+(const List & other);
			List & operator+=(const List & other);
			
			//Iterators.
			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;
			
			reverse_iterator rbegin();
			reverse_iterator rend();
			const_reverse_iterator rbegin() const;
			const_reverse_iterator rend() const;
			
			//Description.
			operator std::string() const;
		};
	}
}
