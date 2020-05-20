#include "Vector2D.h"

Vector2D::Vector2D() {}

Vector2D::Vector2D(int eX, int eY) {
	X = eX;
	Y = eY;
}

//return magnitude of the vector
float Vector2D::magnitude() {
	return sqrtf(powf(X, 2) + powf(Y, 2));
}