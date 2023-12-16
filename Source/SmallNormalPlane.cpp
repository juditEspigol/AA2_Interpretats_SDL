#include "SmallNormalPlane.h"

SmallNormalPlane::SmallNormalPlane(MovementType movement, bool isRight)
	: EnemyPlane(1, 50), currentMove(movement), isRight(isRight)
{
	fireTime = 1.00f;
	lastFireTime = 0.0f;
	speed = Vector2(12, 22); 

	movementTime = 0.0f; 

	// TRANSFORM
	if(isRight)
		transform.position = Vector2(10 +rand() % (int)RENDERER.GetSizeWindow().x * 0.40, 0);
	else
		transform.position = Vector2((int)RENDERER.GetSizeWindow().x * 0.6 + rand() % (int)RENDERER.GetSizeWindow().x * 0.30, 0);
	transform.angle = 180.0f;
	transform.scale = Vector2(2.0f, 2.0f);
	transform.size = Vector2(16, 16);
	// RENDER
	renderer = new ImageRenderer(&transform, Vector2(5, 161), Vector2(15, 15));
	// RIGID BODY 
	rb = new RigidBody(&transform);
	Vector2 topLeft = transform.position - transform.size / 2;
	rb->AddCollision(new AABB(topLeft, transform.size));
	rb->SetLinearDrag(7);
}

void SmallNormalPlane::Update(float dt)
{
	EnemyPlane::Update(dt);

	movementTime += dt; 
	UpdateMovementPattern(dt); 
}

void SmallNormalPlane::UpdateMovementPattern(float dt)
{
	Vector2 force = Vector2(); 

	switch (currentMove)
	{
	case SmallNormalPlane::V:

		if (isRight)
			force.x += 1; 
		else
			force.x -= 1;

		if (movementTime >= 2.0)
			force.y -= 1; 
		else
			force.y += 1;
		break;
	case SmallNormalPlane::CURVE:

		if (movementTime >= 1.5f && movementTime <= 2.1f)
		{
			force = Vector2(cos(movementTime * 3.1416), -sin(movementTime * 3.1416));
			SetRotation(GetRotation() - (90 * dt) * 1.75);
		}
		else if (movementTime <= 1.5f)
		{
			force.y += speed.y;
		}
		else
		{
			force.x += speed.y;
			SetRotation(90); 
		}
		break;
	case SmallNormalPlane::STRAIGHT:
		force.y += 1;
		break;
	default:
		break;
	}

	force.Normalize();
	force = force * speed;
	rb->AddForce(force);
}