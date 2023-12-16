#include "SmallRedPlane.h"

SmallRedPlane::SmallRedPlane(bool isRight, bool isUp)
	: EnemyPlane(1, 100), isRight(isRight), isUp(isUp)
{
	fireTime = 1.10f;
	lastFireTime = 0.0f;
	speed = Vector2(20, 20); 
	isLooping = false;
	startLoop = 2.0f; 

	// TRANSFORM
	transform.size = Vector2(16, 16);
	float randomPosY = 120 + rand() % (int)RENDERER.GetSizeWindow().y * 0.25; 
	if (isRight)
	{
		transform.position = Vector2(-transform.size.x, randomPosY);
		transform.angle = -90.0f;
	}
	else
	{
		transform.position = Vector2(RENDERER.GetSizeWindow().x + transform.size.x, randomPosY);
		transform.angle = 90.0f;
	}
	transform.scale = Vector2(2.0f, 2.0f);
	transform.size = Vector2(16, 16);
	// RENDER
	renderer = new ImageRenderer(&transform, Vector2(7, 283), Vector2(15, 15));
	// RIGID BODY 
	rb = new RigidBody(&transform);
	Vector2 topLeft = transform.position - transform.size / 2;
	rb->AddCollision(new AABB(topLeft, transform.size));
	rb->SetLinearDrag(7);
}

void SmallRedPlane::Update(float dt)
{
	EnemyPlane::Update(dt); 

	movementTime += dt; 

	UpdateMovementPattern(dt);
}

void SmallRedPlane::UpdateMovementPattern(float dt)
{
	Vector2 force = Vector2();

	// Check if start loop
	if (movementTime >= startLoop && movementTime <= startLoop + 2.0f) // 1 loop = 2s 
		isLooping = true;
	else
		isLooping = false;

	//Apply force
	if (isRight)
	{
		if (isLooping)
		{
			if (isUp)
			{
				force = Vector2(cos(movementTime * 3.1416), -sin(movementTime * 3.1416));
				SetRotation(GetRotation() - 180.0f * dt);
			}
			else
			{
				force = Vector2(cos(movementTime * 3.1416), sin(movementTime * 3.1416));
				SetRotation(GetRotation() + 180.0f * dt);
			}
		}
		else
			force.x += 1;
	}
	else
	{
		if (isLooping)
		{
			if (isUp)
			{
				force = Vector2(-cos(movementTime * 3.1416), -sin(movementTime * 3.1416));
				SetRotation(GetRotation() + 180.0f * dt);
			}
			else
			{
				force = Vector2(-cos(movementTime * 3.1416), sin(movementTime * 3.1416));
				SetRotation(GetRotation() - 180.0f * dt);
			}
		}
		else
			force.x -= 1;
	}
	force.Normalize();
	force = force * speed;
	rb->AddForce(force);
}