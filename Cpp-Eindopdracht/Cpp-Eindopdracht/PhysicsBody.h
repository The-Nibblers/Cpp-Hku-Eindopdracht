#pragma once
#include "Vector2.h"

class PhysicsBody
{
public:
	Vector2 transform;
	Vector2 velocity;
	Vector2 acelleration;

	int gravityForce;

	void HandlePhysics();

private:
	void ApplyGravity();
	void ApplyFriction();
	void ApplyAccelleration();
	void ApplyVelocity();
};

