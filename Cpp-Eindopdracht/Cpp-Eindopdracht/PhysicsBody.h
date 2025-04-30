#pragma once
#include "Vector2.h"

enum Direction {
	Up,
	Down,
	Left,
	Right

};

class PhysicsBody
{
public:
	Vector2 transform;
	Vector2 velocity;
	Vector2 acelleration;

	int gravityModifier;
	int mass;
	int accellerationTime;

	void HandlePhysics();

private:
	void ApplyGravity();
	void ApplyFriction();
	void ApplyForce(Vector2 target, int Force, Direction direction);
	void ApplyAccelleration(Vector2 target, Vector2 appliedForce);
	void ApplyVelocity();
};

