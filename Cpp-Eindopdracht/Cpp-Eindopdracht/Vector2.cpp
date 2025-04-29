#include "Vector2.h"

Vector2::Vector2(int xVal, int yVal)
	: x(xVal), y(yVal)
{
	
}

Vector2 Vector2::operator+(const Vector2& otherVector)
{
	return Vector2(x + otherVector.x, y + otherVector.y);
}

Vector2 Vector2::operator-(const Vector2& otherVector)
{
	return Vector2(x - otherVector.x, y - otherVector.y);
}

int Vector2::GetX()
{
	return x;
}

int Vector2::GetY()
{
	return y;
}
