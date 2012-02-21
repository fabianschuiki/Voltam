#pragma once
#include <cstdlib>

class Vector
{
	public:
		int64_t x, y;

		Vector() { x = 0; y = 0; }
		Vector(int64_t x, int64_t y) { this->x = x; this->y = y; }
};
