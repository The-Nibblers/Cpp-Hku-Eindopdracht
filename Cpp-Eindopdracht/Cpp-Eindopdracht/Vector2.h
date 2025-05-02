#pragma once
class Vector2
{
private:
	float x;
	float y;

public:
	Vector2();
	Vector2(float xVal, float yVal);

	Vector2 operator+(const Vector2& otherVector);
	Vector2 operator- (const Vector2& otherVector);
	Vector2 operator* (const Vector2& otherVector);
	Vector2 operator/ (const Vector2& otherVector);
	float GetX();
	float GetY();
};