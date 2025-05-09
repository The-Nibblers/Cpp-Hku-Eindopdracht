#include "PhysicsBody.h"
#include <iostream>

PhysicsBody::PhysicsBody(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier)
{
	transform = _transform;
	gravityModifier = _gravityModifier;
	mass = _mass;
	frictionModifier = _frictionModifier;
}

void PhysicsBody::HandlePhysics(float deltaTime)
{
	ApplyGravity();
	ApplyFriction(deltaTime);
	ApplyVelocity(deltaTime);
}

Vector2 PhysicsBody::GetPosition()
{
	return transform;
}

void PhysicsBody::ApplyGravity()
{
	float gravityForce = mass * gravityModifier;
	gravityForce *= 0.1f;
	ApplyForce(gravityForce, Down);
}

void PhysicsBody::ApplyFriction(float deltaTime)
{
	float damping = std::pow(1.0f - frictionModifier, deltaTime);
	velocity = velocity * Vector2(damping, damping);
}

void PhysicsBody::ApplyForce(float Force, Direction direction)
{
	Vector2 appliedForce;
	switch (direction)
	{
	case Up:    appliedForce = Vector2(0, -Force); break;
	case Down:  appliedForce = Vector2(0, Force); break;
	case Left:  appliedForce = Vector2(-Force, 0); break;
	case Right: appliedForce = Vector2(Force, 0); break;
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