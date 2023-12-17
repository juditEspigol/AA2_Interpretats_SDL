#include "MediumYellowPlane.h"

MediumYellowPlane::MediumYellowPlane(bool isRight, Player* playerReference)
	: EnemyPlane(12, 2530, playerReference), isRight(isRight)
{
	fireTime = 1.00f;
	lastFireTime = 0.0f;
	speed = Vector2(20, 20); 
	isLooping = false; 
	startLoop = 1.5f; 

	// TRANSFORM
	transform.size = Vector2(32, 32);
	//int randomPosX = 
	if(isRight)
		transform.position = Vector2(RENDERER.GetSizeWindow().x * 0.25, -transform.size.y * 0.75);
	else
		transform.position = Vector2(RENDERER.GetSizeWindow().x * 0.75, -transform.size.y * 0.75);
	transform.angle = 0.0f;
	transform.scale = Vector2(2.0f, 2.0f);
	// RENDER
	renderer = new ImageRenderer(&transform, Vector2(7, 501), Vector2(31, 23));
	// RIGID BODY 
	rb = new RigidBody(&transform);
	Vector2 topLeft = transform.position - transform.size / 2;
	rb->AddCollision(new AABB(topLeft, transform.size));
	rb->SetLinearDrag(7);
}

void MediumYellowPlane::Update(float dt)
{
	EnemyPlane::Update(dt);

	movementTime += dt;

	UpdateMovementPattern(dt);
}

void MediumYellowPlane::UpdateMovementPattern(float dt)
{
	Vector2 force = Vector2();

	// Check if start loop
	if (movementTime >= startLoop && movementTime <= startLoop + 3.5f) // 1 loop = 4s 
		isLooping = true;
	else
		isLooping = false;

	//Apply force
	if (isLooping)
	{
		if (isRight)
		{
			force = Vector2(-cos(movementTime * 3.1416 * 0.5), sin(movementTime * 3.1416 * 0.5) * 0.25);
			SetRotation(GetRotation() - (90 * dt) * 1.15);
		}
		else
		{
			force = Vector2(cos(movementTime * 3.1416 * 0.5), sin(movementTime * 3.1416 * 0.5) * 0.25);
			SetRotation(GetRotation() + (90 * dt) * 1.15);
		}
	}
	else
	{
		SetRotation(0.0f); 
		force.y += 1;
	}

	force.Normalize();
	force = force * speed;
	rb->AddForce(force);
}