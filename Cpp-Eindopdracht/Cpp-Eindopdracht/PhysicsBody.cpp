#include "PhysicsBody.h"
#include <iostream>

void PhysicsBody::HandlePhysics()
{
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
	switch (direction)
	{
	case Up:
		Vector2 appliedForce = Vector2(target.GetX(), target.GetY() + Force);
		break;
	case Down:
		Vector2 appliedForce = Vector2(target.GetX(), target.GetY() - Force);
		break;
	case Left:
		Vector2 appliedForce = Vector2(target.GetX() - Force, target.GetY());
		break;
	case Right:
		Vector2 appliedForce = Vector2(target.GetX() + Force, target.GetY());
		break;
	default:
		std::cout << "unkown direction";
		break;
	}

}

void PhysicsBody::ApplyAccelleration(Vector2 target, Vector2 appliedForce)
{
	Vector2 Accelleration = Vector2(appliedForce.GetX() / mass, appliedForce.GetY() / mass);

}

void PhysicsBody::ApplyVelocity()
{

}
