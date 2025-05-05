#include "Player.h"

Player::Player(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier, float _moveSpeed) : PhysicsBody(_transform,_gravityModifier,_mass, _frictionModifier)
{
	moveSpeed = _moveSpeed;
}

void Player::MoveLeft()
{
	ApplyForce(transform, moveSpeed, Left);
}

void Player::MoveRight()
{
	ApplyForce(transform, moveSpeed, Right);
}
