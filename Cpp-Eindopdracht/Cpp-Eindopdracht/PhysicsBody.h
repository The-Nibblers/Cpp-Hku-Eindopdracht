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

	float gravityModifier;
	float mass;
	//int accellerationTime;

	PhysicsBody(Vector2 _transform, float _gravityModifier, float _mass);

	void HandlePhysics(float deltaTime);
	Vector2 GetPosition();

private:
	void ApplyGravity();
	void ApplyFriction();
	void ApplyForce(Vector2 target, int Force, Direction direction);
	void ApplyAccelleration(Vector2 appliedForce);
	void ApplyVelocity(float deltaTime);
};

