#pragma once
#include <cmath>
#include <sstream>
#include <string>


namespace math
{
	template <typename T>
	class Vector2D
	{
	public:
		T x;
		T y;
		
		//Description
		std::string description() const {
			std::stringstream s;
			s << "(" << x << ", " << y << ")";
			return s.str();
		}
		
		//Conversion to frequently used types
		inline operator Vector2D<int>()    const { return Vector2D<int>   (x, y); }
		inline operator Vector2D<float>()  const { return Vector2D<float> (x, y); }
		inline operator Vector2D<double>() const { return Vector2D<double>(x, y); }
		
		//Constructors
		Vector2D()
		{
			x = 0;
			y = 0;
		}
		Vector2D(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		
		//Operators
		Vector2D<T>& operator= (Vector2D<T> v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}
		Vector2D<T> operator- () const	{ return Vector2D<T>(-x, -y); }
		
		//Boolean operators
		bool operator ==(Vector2D<T> v) const {
			return (x == v.x && y == v.y);
		}
		bool operator !=(Vector2D<T> v) const {
			return (x != v.x || y != v.y);
		}
		
		//Vector-Vector
		inline Vector2D<T> operator+ (Vector2D<T> v) const	{ return Vector2D<T>(x+v.x, y+v.y); }
		inline Vector2D<T> operator- (Vector2D<T> v) const	{ return Vector2D<T>(x-v.x, y-v.y); }
		inline Vector2D<T> operator* (Vector2D<T> v) const	{ return Vector2D<T>(x*v.x, y*v.y); }
		inline Vector2D<T> operator/ (Vector2D<T> v) const	{ return Vector2D<T>(x/v.x, y/v.y); }
		
		//Vector-Scalar
		inline Vector2D<T> operator+ (T v) const	{ return Vector2D<T>(x+v, y+v); }
		inline Vector2D<T> operator- (T v) const	{ return Vector2D<T>(x-v, y-v); }
		inline Vector2D<T> operator* (T v) const	{ return Vector2D<T>(x*v, y*v); }
		inline Vector2D<T> operator/ (T v) const	{ return Vector2D<T>(x/v, y/v); }
		
		//Vector-Vector
		inline Vector2D<T>& operator+= (Vector2D<T> v)	{ x += v.x; y += v.y; return *this; }
		inline Vector2D<T>& operator-= (Vector2D<T> v)	{ x -= v.x; y -= v.y; return *this;	}
		inline Vector2D<T>& operator*= (Vector2D<T> v)	{ x *= v.x; y *= v.y; return *this; }
		inline Vector2D<T>& operator/= (Vector2D<T> v)	{ x /= v.x; y /= v.y; return *this; }
		
		//Vector-Scalar
		inline Vector2D<T>& operator+= (T v)	{ x += v; y += v; return *this; }
		inline Vector2D<T>& operator-= (T v)	{ x -= v; y -= v; return *this; }
		inline Vector2D<T>& operator*= (T v)	{ x *= v; y *= v; return *this; }
		inline Vector2D<T>& operator/= (T v)	{ x /= v; y /= v; return *this; }
		
		//Operations
		inline T length2() const { return x*x + y*y; }
		inline T length()  const { return sqrt(length2()); }
		
		inline Vector2D<T> unit() const
		{
			Vector2D<T> v = *this;
			v.unitize();
			return v;
		}
		inline T unitize()
		{
			T l = this->length();
			x /= l;
			y /= l;
			return l;
		}
		
		inline T dot(Vector2D<T> v) const
		{
			return (x*v.x + y*v.y);
		}
		
		inline void fromStack(lua_State * L, int index)
		{
			lua_pushnil(L);
			lua_next(L, index-1); x = lua_tonumber(L, -1); lua_pop(L, 1);
			lua_next(L, index-1); y = lua_tonumber(L, -1); lua_pop(L, 1);
			lua_pop(L, 1);
		}
	};
}

//Convenience typedefs
typedef math::Vector2D<int> int2;
typedef math::Vector2D<float> float2;
typedef math::Vector2D<double> double2;
