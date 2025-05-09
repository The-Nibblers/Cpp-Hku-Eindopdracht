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
	float frictionModifier;
	float mass;
	

	PhysicsBody(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier);

	void HandlePhysics(float deltaTime);
	void ApplyForce(float Force, Direction direction);
	Vector2 GetPosition();

private:
	void ApplyGravity();
	void ApplyFriction(float deltaTime);
	void ApplyAccelleration(Vector2 appliedForce);
	void ApplyVelocity(float deltaTime);
};

