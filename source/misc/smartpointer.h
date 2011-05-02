#pragma once

#include <map>
#include <assert.h>
#include <iostream>


namespace Voltam {
	/**
	 * AbstractSmartPointer
	 *
	 * Hosts one shared map that associates a pointer with a retain count. The templated smart
	 * pointer is derived from the abstract version and uses its retain and release functions to
	 * modify the retain count table.
	 */
	class AbstractSmartPointer {
		
		//Map associating a pointer and a retain count.
		static std::map<void *, long> rc;
		
	public:
		//Increases the retain count of the given pointer. If the pointer is not yet present in the
		//map a new entry is created.
		template <typename T> void retain(T * obj) {
			if (!rc.count(obj))
				rc[obj] = 0;
			rc[obj]++;
		}
		
		//Decreases the retain count of the given pointer. If the count reaches zero the pointer is
		//deleted immediately. The pointer will blow up if the object trying to be deleted is not in
		//the map.
		template <typename T> void release(T * obj) {
			assert(rc.count(obj) && "trying to release an unmanaged pointer");
			rc[obj]--;
	
			if (rc[obj] <= 0) {
				rc.erase(obj);
				delete obj;
			}
		}
	};
	
	
	/**
	 * SmartPointer
	 *
	 * Wraps a pointer to a class specified through the tempalte parameter T. Assigning an object to
	 * the smart pointer will cause it to increase the object's retain count in the shared retain
	 * count map. If the assignment overwrites an existing object assigned to the pointer, the
	 * latter's retain count is decreased.
	 *
	 * It is okay to access an object by its raw pointer in parallel to having it assigned in a
	 * samrt pointer, as long as you can guarantee that at the time you're using the object direct-
	 * ly there's a smart pointer around somewhere safeguarding its existence.
	 *
	 * It is however ABSOLUTELY NOT okay to delete objects still safeguarded by a smart pointer.
	 */
	template <class T>
	class SmartPointer : private AbstractSmartPointer {
		T * obj;
		
	public:
		//Construction
		SmartPointer() : obj(NULL) {}
		
		SmartPointer(T * o) : obj(NULL) { *this = o; }
		SmartPointer(const SmartPointer<T> & p) : obj(NULL) { *this = p; }
		
		template <class C> SmartPointer(C * o) : obj(NULL) { *this = o; }
		template <class C> SmartPointer(const SmartPointer<C> & p) : obj(NULL) { *this = p; }
		
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
		
		template <class C> SmartPointer<T> & operator =(C * o) { *this = static_cast<T*>(o); }
		template <class C> SmartPointer<T> & operator =(const SmartPointer<C> & p) { *this = static_cast<T*>(p); }
		
		//Dereferencing operators that provide some transparency so that using the smart pointer
		//feels the same as using the raw pointer itself.
		T& operator *() const {
			assert(obj != NULL && "tried to * on a NULL pointer");
			return *obj;
		}
		T* operator ->() const {
			assert(obj != NULL && "tried to -> on a NULL pointer");
			return obj;
		}
		
		//In case something needs the object itself instead of the raw pointer, we silently step out
		//of the way.
		operator T*() const { return obj; }
		template <class C> operator C*() const { return static_cast<C*>(obj); }
		
		//Checking for pointer validity.
		inline operator bool() const { return (bool)obj; }
		inline bool operator !() const { return !(obj); }
		
		//Comparing to pointers and smart pointers.
		inline bool operator ==(const T * o) const { return (obj == o); }
		inline bool operator ==(const SmartPointer<T> & p) const { return (obj == p.obj); }
	};
}

