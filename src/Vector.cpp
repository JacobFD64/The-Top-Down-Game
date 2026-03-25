#include <cmath>

#include "Vector.h"

Vector::Vector(float x, float y) : x(x), y(y) {}

void Vector::normalise()
{
	float magnitude = sqrt(x * x + y * y);
	x /= magnitude;
	y /= magnitude;
}

Vector Vector::operator*(float scalar)
{
	return Vector(x * scalar, y * scalar);
}