#pragma once

#include <map>
#include <assert.h>
#include <iostream>


namespace Voltam {
	class AbstractSmartPointer {
		static std::map<void *, long> rc;
		
	public:
		template <typename T> void retain(T * obj) {
			std::cout << "retain " << obj << std::endl;
			if (!rc.count(obj))
				rc[obj] = 0;
			rc[obj]++;
		}
		
		template <typename T> void release(T * obj) {
			std::cout << "release " << obj << std::endl;
			assert(rc.count(obj) && "trying to release an unmanaged pointer");
			rc[obj]--;
	
			if (rc[obj] <= 0) {
				rc.erase(obj);
				delete obj;
				std::cout << "# deleted " << obj << ", " << rc.size() << " objects left" << std::endl;
			}
		}
	};
	
	template <class T>
	class SmartPointer : private AbstractSmartPointer {
		T * obj;
		
	public:
		//Construction
		SmartPointer() : obj(NULL) {}
		SmartPointer(T * o) : obj(NULL) { *this = o; }
		SmartPointer(const SmartPointer<T> & p) : obj(NULL) { *this = p; }
		
		~SmartPointer() { if (obj) release(obj); obj = NULL; }
		
		//Assignment
		SmartPointer<T> & operator =(T * o) {
			if (o) retain(o);
			if (obj) release(obj);
			obj = o;
			return *this;
		}
		SmartPointer<T> & operator =(const SmartPointer<T> & p) {
			if (p.obj) retain(p.obj);
			if (obj) release(obj);
			obj = p.obj;
			return *this;
		}
		
		//Dereferencing
		T & operator *() const {
			assert(obj != NULL && "tried to * on a NULL pointer");
			return *obj;
		}
		T * operator ->() const {
			assert(obj != NULL && "tried to -> on a NULL pointer");
			return obj;
		}
		
		//Auto Typecast
		operator T *() const { return obj; }
		
		//Logic
		inline operator bool() const { return (bool)obj; }
		inline bool operator !() const { return !(obj); }
		
		inline bool operator ==(const T * o) const { return (obj == o); }
		inline bool operator ==(const SmartPointer<T> & p) const { return (obj == p.obj); }
	};
}

