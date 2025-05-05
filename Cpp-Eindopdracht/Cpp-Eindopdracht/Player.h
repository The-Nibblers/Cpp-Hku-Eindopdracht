#pragma once
#include "PhysicsBody.h"
#include "Vector2.h"

class Player : PhysicsBody
{
public: 
	float moveSpeed;

	Player(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier);
	void MoveLeft();
	void MoveRight();

private:

};

