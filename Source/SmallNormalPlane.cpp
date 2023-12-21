#include "SmallNormalPlane.h"

SmallNormalPlane::SmallNormalPlane(MovementType _movement, bool _isRight, Transform* _playerTransform)
	: EnemyPlane(1, 50, _playerTransform), currentMove(_movement), isRight(_isRight), timeToGoUp(2.0f), pixelsPorSecond(Vector2(1, 3))
{

	timeToCurve = 1.5f; 
	radioCurve = 5; 

	// TRANSFORM
	transform = new Transform();
	if(isRight)
		transform->position = Vector2(10 +rand() % (int)RENDERER.GetSizeWindow().x * 0.40, 0);
	else
		transform->position = Vector2((int)RENDERER.GetSizeWindow().x * 0.6 + rand() % (int)RENDERER.GetSizeWindow().x * 0.30, 0);
	transform->angle = 180.0f;
	transform->scale = Vector2(2.0f, 2.0f);
	transform->size = Vector2(16, 16);

	// RENDER
	renderer = new ImageRenderer(transform, Vector2(5, 161), Vector2(15, 15));

	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void SmallNormalPlane::Update(float dt)
{
	EnemyPlane::Update(dt);

	Shoot(); 

	UpdateMovementPattern(dt); 
}

void SmallNormalPlane::UpdateMovementPattern(float dt)
{
	switch (currentMove)
	{
	case SmallNormalPlane::V:

		MovementV(); 
		break;
	case SmallNormalPlane::CURVE:
		
		MovementCurve(dt); 
		break;
	case SmallNormalPlane::STRAIGHT:

		MovementStraight(); 
		break;
	default:
		break;
	}
}

void SmallNormalPlane::MovementV()
{
	Vector2 direction = pixelsPorSecond;

	if (isRight)
		direction.x *= 1;
	else
		direction.x *= -1;

	if (movementTime >= timeToGoUp)
		direction.y *= -1;
	else
		direction.y *= 1;

	transform->position = transform->position + direction; 
}

void SmallNormalPlane::MovementCurve(float dt)
{
	Vector2 direction = Vector2();

	if (movementTime <= timeToCurve) // GO STRAIGHT DOWN
	{
		direction = Vector2(0, pixelsPorSecond.y); 
	}
	else if (movementTime >= timeToCurve && movementTime <= (timeToCurve + 0.5)) // CURVE // 0.5 -> duration 1/4 of the loop
	{
		if (isRight)
		{
			direction = Vector2(cos(movementTime * PI) * radioCurve, -sin(movementTime * PI) * radioCurve); // 2 second == 1 loop
			SetRotation(GetRotation() - (180 * dt));
		}
		else
		{
			direction = Vector2(-cos(movementTime * PI) * radioCurve, -sin(movementTime * PI) * radioCurve); // 2 second == 1 loop
			SetRotation(GetRotation() + (180 * dt));
		}
	}
	else // GO STRAIGHT LEFT/RIGHT
	{
		if (isRight)
			direction = Vector2(pixelsPorSecond.y, 0);
		else
			direction = Vector2(-pixelsPorSecond.y, 0);
	}

	transform->position = transform->position + direction;
}

void SmallNormalPlane::MovementStraight()
{
	transform->position = transform->position + Vector2(0, pixelsPorSecond.y);
}
