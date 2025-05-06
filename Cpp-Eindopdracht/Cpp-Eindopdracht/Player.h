#pragma once
#include "PhysicsBody.h"
#include "Vector2.h"

class Player : public PhysicsBody
{
public:

	Player(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier, float _moveSpeed, int _borderSizeX, int _borderSizeY, float _radius);
	void MoveLeft();
	void MoveRight();
	void BorderDetection();

private:
	float moveSpeed;
	int borderSizeY;
	int bordersizeX;
	float radius;
};

