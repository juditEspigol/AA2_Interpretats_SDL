#include "SmallNormalPlane.h"

SmallNormalPlane::SmallNormalPlane(MovementType _movement, bool _isRight, Transform* _playerTransform)
	: EnemyPlane(1, 50, _playerTransform), currentMove(_movement), isRight(_isRight)
{
	pixelsPorSecond = Vector2(2, 3);

	changeMoveTime = 1.5f;
	radiusLoop = 4;

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
	renderers.emplace("Idle", new ImageRenderer(transform, Vector2(5, 161), Vector2(15, 15)));
	DeathAnimation(); 
	renderer = renderers["Idle"];

	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
}

void SmallNormalPlane::Update(float dt)
{
	EnemyPlane::Update(dt);

	if (isAlive)
	{
		Shoot();
		UpdateMovementPattern(dt);
	}
	else
		DeathState(); 
}

void SmallNormalPlane::UpdateMovementPattern(float dt)
{
	switch (currentMove)
	{
	case SmallNormalPlane::V:

		MovementV(dt); 

		break;

	case SmallNormalPlane::CURVE:
	
		MovementCurve(dt); 

		break;

	case SmallNormalPlane::STRAIGHT:

		MovementStraight(dt); 

		break;

	default:
		break;
	}
}

void SmallNormalPlane::MovementV(float dt)
{
	Vector2 direction = pixelsPorSecond;

	if (isRight)
		direction.x *= 1;
	else
		direction.x *= -1;

	if (movementTime >= changeMoveTime)
	{
		direction.y *= -1;
		if (isRight)
		{
			if (GetRotation() > 45)
				SetRotation(GetRotation() - (360 * dt));
			else
				SetRotation(45);
		}
		else
		{
			if (GetRotation() < 315)
				SetRotation(GetRotation() + (360 * dt));
			else
				SetRotation(315);
		}
	}
	else
	{
		if(isRight)
			SetRotation(135);
		else
			SetRotation(225);
		direction.y *= 1;
	}

	transform->position = transform->position + direction; 
}

void SmallNormalPlane::MovementCurve(float dt)
{
	Vector2 direction = pixelsPorSecond;

	if (movementTime <= changeMoveTime) // GO STRAIGHT DOWN
	{
		if (isRight)
		{
			direction.x *= 1;
			SetRotation(135);
		}
		else
		{
			direction.x *= -1;
			SetRotation(225);
		}
	}
	else if (movementTime >= changeMoveTime && movementTime <= (changeMoveTime + 0.5f)) // CURVE
	{
		if (isRight)
			direction = Loop(dt, -1, -1); 
		else
			direction = Loop(dt, 1, -1);
	}
	else // CONTINUE STRAIGHT
	{
		if (!isRight)
			direction.x *= 1;
		else
			direction.x *= -1;
	}

	transform->position = transform->position + direction;
}

void SmallNormalPlane::MovementStraight(float dt)
{
	Vector2 direction = pixelsPorSecond;

	if (isRight)
	{
		direction.x *= 1;
		SetRotation(135);
	}
	else
	{
		direction.x *= -1;
		SetRotation(225);
	}
	direction.y *= 1;

	transform->position = transform->position + direction;
}

Vector2 SmallNormalPlane::Loop(float dt, int cosSigne, int sinSigne)
{
	Vector2 pos = Vector2();
	pos = Vector2(cosSigne * cos(movementTime * M_PI) * radiusLoop,
		sinSigne * sin(movementTime * M_PI) * radiusLoop);
	SetRotation(GetRotation() - cosSigne * 180 * dt);

	return pos;
}

void SmallNormalPlane::DeathAnimation()
{
	std::vector<Vector2> deathDeltas{
		Vector2(0, 0),
		Vector2(20, 0),
		Vector2(20 * 2, 0),
		Vector2(20 * 3, 0),
		Vector2(20 * 4, 0),
		Vector2(20 * 5, 0)
	};
	renderers.emplace("Death", new AnimatedImageRenderer(transform, Vector2(157, 80), Vector2(20, 20), deathDeltas, false, 20));
}
