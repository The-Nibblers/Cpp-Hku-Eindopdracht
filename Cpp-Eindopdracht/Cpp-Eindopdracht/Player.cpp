#include "Player.h"
#include <cmath>
#include <IOstream>

Player::Player(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier, float _moveSpeed, int _borderSizeX, int _borderSizeY, float _radius) : PhysicsBody(_transform,_gravityModifier,_mass, _frictionModifier)
{
	moveSpeed = _moveSpeed;
	bordersizeX = _borderSizeX;
	borderSizeY = _borderSizeY;
	radius = _radius;
}

void Player::MoveLeft()
{
	ApplyForce(moveSpeed, Left);
}

void Player::MoveRight()
{
	ApplyForce(moveSpeed, Right);
}

void Player::BorderDetection()
{
	if (transform.x <= (0 + radius) ) {
		velocity = Vector2(0,0);
		ApplyForce(1, Right);
	}
	if (transform.x >= bordersizeX - radius) {
		velocity = Vector2(0, 0);
		ApplyForce(1, Left);
	}
}

bool Player::CollisionDetection(Vector2 obj1, Vector2 obj2, float radius1, float radius2)
{
	if ((pow(obj2.GetX() - obj1.GetX(), 2) +
		pow(obj2.GetY() - obj1.GetY(), 2)) <=
		pow(radius1 + radius2, 2)) {
		return true;
	}
	else
	{
		return false;
	}
}