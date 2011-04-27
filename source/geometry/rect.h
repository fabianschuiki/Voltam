#pragma once

#include "vector2d.h"


namespace Voltam {
	namespace Geometry {
		template <typename T>
		class Rect {
		public:
			Vector2D<T> origin;
			Vector2D<T> size;
			
			//Construction
			Rect(const Vector2D<T> & origin, const Vector2D<T> & size) : origin(origin), size(size) {}
			Rect(T x, T y, T w, T h) : origin(x, y), size(w, h) {}
			
			//Copying
			Rect(const Rect<T> * r) : origin(r->origin), size(r->size) {}
			Rect(const Rect<T> & r) : origin(r.origin), size(r.size) {}
			
			//Assignment
			inline Rect<T> & operator=(const Rect<T> & r) { origin = r.origin; size = r.size; return *this; }
			inline Rect<T> operator-() const { return Rect<T>(-origin, -size); }
			
			//Comparison
			inline bool operator==(const Rect<T> & r) const { return (origin == r.origin && size == r.size); }
			inline bool operator!=(const Rect<T> & r) const { return (origin != r.origin && size != r.size); }
			
			//Coordinates
			inline T minX() const { return origin.x; }
			inline T minY() const { return origin.y; }
			inline T midX() const { return origin.x + size.x / 2; }
			inline T midY() const { return origin.y + size.y / 2; }
			inline T maxX() const { return origin.x + size.x; }
			inline T maxY() const { return origin.y + size.y; }
			
			//Points
			inline Vector2D<T> minXminY() const { return Vector2D<T>(minX(), minY()); }
			inline Vector2D<T> minXmidY() const { return Vector2D<T>(minX(), midY()); }
			inline Vector2D<T> minXmaxY() const { return Vector2D<T>(minX(), maxY()); }
			inline Vector2D<T> midXminY() const { return Vector2D<T>(midX(), minY()); }
			inline Vector2D<T> center()	  const { return Vector2D<T>(midX(), midY()); }
			inline Vector2D<T> midXmaxY() const { return Vector2D<T>(midX(), maxY()); }
			inline Vector2D<T> maxXminY() const { return Vector2D<T>(maxX(), minY()); }
			inline Vector2D<T> maxXmidY() const { return Vector2D<T>(maxX(), midY()); }
			inline Vector2D<T> maxXmaxY() const { return Vector2D<T>(maxX(), maxY()); }
			
			//Conversion
			inline operator Rect<int>() const { return Rect<int>(origin, size); }
			inline operator Rect<float>() const { return Rect<float>(origin, size); }
			inline operator Rect<double>() const { return Rect<double>(origin, size); }
			
			//Description
			operator std::string() const { std::stringstream s; s << "(" << origin << ", " << size << ")"; return s.str(); }
		};
	}
	
	//Convenience typedefs.
	typedef Geometry::Rect<int> recti;
	typedef Geometry::Rect<float> rectf;
	typedef Geometry::Rect<double> rectd;
}

