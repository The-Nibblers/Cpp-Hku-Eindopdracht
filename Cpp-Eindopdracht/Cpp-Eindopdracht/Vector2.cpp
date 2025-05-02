#include "Vector2.h"

Vector2::Vector2()
	: x(0), y(0)
{
}

Vector2::Vector2(float xVal, float yVal)
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

Vector2 Vector2::operator*(const Vector2& otherVector)
{
	return Vector2(x * otherVector.x, y * otherVector.y);
}

Vector2 Vector2::operator/(const Vector2& otherVector)
{
	return Vector2(x / otherVector.x, y / otherVector.y);
}

float Vector2::GetX()
{
	return x;
}

float Vector2::GetY()
{
	return y;
}
