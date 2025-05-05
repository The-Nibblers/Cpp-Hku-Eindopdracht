#pragma once
#include "PhysicsBody.h"
#include "Vector2.h"

class Player : public PhysicsBody
{
public: 
	float moveSpeed;

	Player(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier, float _moveSpeed);
	void MoveLeft();
	void MoveRight();

private:

};

