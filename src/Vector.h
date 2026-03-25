#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
	float x, y;

	Vector(float x = 0, float y = 0);

	void normalise();
	Vector operator*(float scalar);
};

#endif // VECTOR_H