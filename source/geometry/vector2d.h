#pragma once

#include <string>
#include <sstream>


namespace Voltam {
	namespace Geometry {
		template <typename T>
		class Vector2D {
		public:
			T x;
			T y;
			
			//Construction
			Vector2D() { x = 0; y = 0; }
			Vector2D(const T & x, const T & y) { this->x = x; this->y = y; }
			
			//Copying
			Vector2D(const Vector2D<T> * v) { *this = *v; }
			Vector2D(const Vector2D<T> & v) { *this = v; }
			
			//Assignment
			inline Vector2D<T> & operator=(const Vector2D<T> & v) { x = v.x; y = v.y; return *this; }
			inline Vector2D<T> operator-() const { return Vector2D<T>(-x, -y); }
			
			//Operators
			inline Vector2D<T> operator+(const Vector2D<T> & v) const { return Vector2D<T>(x + v.x, y + v.y); }
			inline Vector2D<T> operator-(const Vector2D<T> & v) const { return Vector2D<T>(x - v.x, y - v.y); }
			inline Vector2D<T> operator*(const T & v) const { return Vector2D<T>(x*v, y*v); }
			inline Vector2D<T> operator/(const T & v) const { return Vector2D<T>(x/v, y/v); }
			
			inline Vector2D<T> & operator+=(const Vector2D<T> & v) { x += v.x; y += v.y; return *this; }
			inline Vector2D<T> & operator-=(const Vector2D<T> & v) { x -= v.x; y -= v.y; return *this; }
			inline Vector2D<T> & operator*=(const T & v) { x *= v; y *= v; return *this; }
			inline Vector2D<T> & operator/=(const T & v) { x /= v; y /= v; return *this; }
			
			//Comparison
			inline bool operator==(const Vector2D<T> & v) const { return (x == v.x && y == v.y); }
			inline bool operator!=(const Vector2D<T> & v) const { return (x != v.x || y != v.y); }
			
			//Length
			inline T length() const { return sqrt(length2()); }
			inline T length2() const { return (x*x + y*y); }
			
			//Unit
			inline Vector2D<T> unit() const { return (*this / length()); }
			inline Vector2D<T> & unitize() { *this /= length(); return *this; }
			
			//Dot product
			inline T dot(const Vector2D<T> & v) const { return (x*v.x + y*v.y); }
			
			//Conversion
			inline operator Vector2D<int>() const { return Vector2D<int>(x, y); }
			inline operator Vector2D<float>() const { return Vector2D<float>(x, y); }
			inline operator Vector2D<double>() const { return Vector2D<double>(x, y); }
			
			//Description
			operator std::string() const { std::stringstream s; s << "(" << x << ", " << y << ")"; return s.str(); }
		};
	}
	
	//Convenience typedefs
	typedef Geometry::Vector2D<int> int2;
	typedef Geometry::Vector2D<float> float2;
	typedef Geometry::Vector2D<double> double2;
}

