#include "Parachutist.h"

int Parachutist::nextId = 0;

Parachutist::Parachutist(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier, float _moveSpeed, int _borderSizeX, int _borderSizeY, float _radius, bool _moveDirection)
	: PhysicsBody(_transform, _gravityModifier, _mass, _frictionModifier)
{
	id = nextId++;
	moveSpeed = _moveSpeed;
	bordersizeX = _borderSizeX;
	borderSizeY = _borderSizeY;
	radius = _radius;
	moveDirection = _moveDirection;

}

void Parachutist::UpdateMovement()
{
	ApplyForce(transform, moveSpeed * 0.2f, moveDirection ? Left : Right);
}

void Parachutist::BorderDetection()
{
	if (transform.x <= (0 + radius)) {
		velocity = Vector2(0, 0);
		ApplyForce(transform, 1, Right);
		moveDirection = false;
	}
	if (transform.x >= bordersizeX - radius) {
		velocity = Vector2(0, 0);
		ApplyForce(transform, 1, Left);
		moveDirection = true;
	}
	if (transform.y >= borderSizeY) {
		markedForDeletion = true;
	}
}

bool operator==(const Parachutist& a, const Parachutist& b) {
	return a.id == b.id;
}
