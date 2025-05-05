#pragma once
class Vector2
{
public:
	float x;
	float y;
	Vector2();
	Vector2(float xVal, float yVal);

	Vector2 operator+(const Vector2& otherVector);
	Vector2 operator- (const Vector2& otherVector);
	Vector2 operator* (const Vector2& otherVector);
	Vector2 operator/ (const Vector2& otherVector);
	float GetX();
	float GetY();
};