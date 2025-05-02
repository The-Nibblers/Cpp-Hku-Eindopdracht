#include "PhysicsBody.h"
#include <iostream>

PhysicsBody::PhysicsBody(Vector2 _transform, float _gravityModifier, float _mass)
{
	transform = _transform;
	gravityModifier = _gravityModifier;
	mass = _mass;
}

void PhysicsBody::HandlePhysics(float deltaTime)
{
	ApplyGravity();
	ApplyVelocity(deltaTime);
}

Vector2 PhysicsBody::GetPosition()
{
	return transform;
}

void PhysicsBody::ApplyGravity()
{
	int gravityForce = mass * gravityModifier;
	ApplyForce(transform, gravityForce, Down);
}

void PhysicsBody::ApplyFriction()
{
}

void PhysicsBody::ApplyForce(Vector2 target, int Force, Direction direction)
{
	Vector2 appliedForce;
	switch (direction)
	{
	case Up:    appliedForce = Vector2(0, -Force); break;
	case Down:  appliedForce = Vector2(0, Force); break;
	case Left:  appliedForce = Vector2(Force, 0); break;
	case Right: appliedForce = Vector2(-Force, 0); break;
	}
	ApplyAccelleration(appliedForce);
}

void PhysicsBody::ApplyAccelleration(Vector2 appliedForce)
{
	Vector2 Accelleration = Vector2(appliedForce.GetX() / mass, appliedForce.GetY() / mass);
	velocity = Vector2(velocity.GetX() + Accelleration.GetX(), velocity.GetY() + Accelleration.GetY());
}

void PhysicsBody::ApplyVelocity(float deltaTime)
{
	transform = Vector2(transform.GetX() + velocity.GetX() * deltaTime, transform.GetY() + velocity.GetY() * deltaTime);
}