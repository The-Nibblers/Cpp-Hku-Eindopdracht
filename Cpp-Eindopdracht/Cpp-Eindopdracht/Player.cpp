#include "Player.h"

Player::Player(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier, float _moveSpeed, int _borderSizeX, int _borderSizeY, float _radius) : PhysicsBody(_transform,_gravityModifier,_mass, _frictionModifier)
{
	moveSpeed = _moveSpeed;
	bordersizeX = _borderSizeX;
	borderSizeY = _borderSizeY;
	radius = _radius;
}

void Player::MoveLeft()
{
	ApplyForce(transform, moveSpeed, Left);
}

void Player::MoveRight()
{
	ApplyForce(transform, moveSpeed, Right);
}

void Player::BorderDetection()
{
	if (transform.x <= 0) {
		velocity = Vector2(0,0);
		ApplyForce(transform, 1, Right);
	}
	if (transform.x >= bordersizeX - (radius * 2)) {
		velocity = Vector2(0, 0);
		ApplyForce(transform, 1, Left);
	}
}
