#pragma once
class Vector2
{
private:
	int x;
	int y;

public:
	Vector2(int xVal, int yVal);

	Vector2 operator+(const Vector2& otherVector);
	Vector2 operator- (const Vector2 & otherVector);
	int GetX();
	int GetY();
};