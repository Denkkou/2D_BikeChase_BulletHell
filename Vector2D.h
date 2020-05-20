#ifndef  aVector2DFile
#define aVector2DFile

#include <cmath>

class Vector2D {
public:
	Vector2D();
	Vector2D(int eX, int eY);

	int X, Y;
	float magnitude();
};

#endif
