#pragma once
#include "PhysicsBody.h"

class Parachutist : public PhysicsBody
{
public:
	Parachutist(Vector2 _transform, float _gravityModifier, float _mass, float _frictionModifier, float _moveSpeed, int _borderSizeX, int _borderSizeY, float _radius, bool _moveDirection);

	void UpdateMovement();
	void BorderDetection();
	Vector2 GetPosition() const { return transform; }
	float radius;
	int id;
	static int nextId;
	bool markedForDeletion = false;

private:
	float moveSpeed;
	int borderSizeY;
	int bordersizeX;
	bool moveDirection;
};

// Compare parachutists by ID
bool operator==(const Parachutist& a, const Parachutist& b);
