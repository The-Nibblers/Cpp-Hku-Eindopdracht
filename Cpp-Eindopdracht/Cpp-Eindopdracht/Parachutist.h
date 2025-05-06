#pragma once
#include "PhysicsBody.h"

class Parachutist : public PhysicsBody
{
public:
	Parachutist(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier, float _moveSpeed, int _borderSizeX, int _borderSizeY, float _radius, bool _moveDirection);

	void UpdateMovement();
	void BorderDetection();

private:
	float moveSpeed;
	int borderSizeY;
	int bordersizeX;
	float radius;
	bool moveDirection;
};

