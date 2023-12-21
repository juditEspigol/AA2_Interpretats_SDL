#include "SmallRedPlane.h"

SmallRedPlane::SmallRedPlane(bool _isRight, bool _isUp, Transform* _playerTransform)
	: EnemyPlane(1, 100, _playerTransform), isRight(_isRight), isUp(_isUp)
{
	fireTime = 1.10f;
	lastFireTime = 0.0f;
	speed = Vector2(20, 20); 
	startLoop = 2.0f; 

	// TRANSFORM
	transform = new Transform();
	transform->size = Vector2(16, 16);
	float randomPosY = 120 + rand() % (int)RENDERER.GetSizeWindow().y * 0.25; 
	if (isRight)
	{
		transform->position = Vector2(-transform->size.x, randomPosY);
		transform->angle = -90.0f;
	}
	else
	{
		transform->position = Vector2(RENDERER.GetSizeWindow().x + transform->size.x, randomPosY);
		transform->angle = 90.0f;
	}
	transform->scale = Vector2(2.0f, 2.0f);
	transform->size = Vector2(16, 16);
	// RENDER
	renderer = new ImageRenderer(transform, Vector2(7, 283), Vector2(15, 15));
	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void SmallRedPlane::Update(float dt)
{
	EnemyPlane::Update(dt); 

	UpdateMovementPattern(dt);
}

void SmallRedPlane::UpdateMovementPattern(float dt)
{
	Vector2 direction = Vector2();

	if (movementTime >= startLoop && movementTime <= (startLoop + 2.0f))
	{
		if (isRight)
			direction = Loop(dt, 1, -1);
		else
			direction = Loop(dt, -1, 1);
	}
	else
	{
		if(isRight)
			direction = Vector2(pixelsPorSecond.x, 0);
		else
			direction = Vector2(-pixelsPorSecond.x, 0);
	}
	
	transform->position = transform->position + direction;
}

Vector2 SmallRedPlane::Loop(float dt, int cosSigne, int sinSigne)
{
	Vector2 pos = Vector2();
	if (isUp)
	{
		pos = Vector2( cosSigne * cos(movementTime * PI) * radiusLoop, sinSigne * sin(movementTime * PI) * radiusLoop);
		SetRotation(GetRotation() - 180 * dt);
	}
	else
	{
		pos = Vector2(cosSigne * cos(movementTime * PI) * radiusLoop, -sinSigne * sin(movementTime * PI) * radiusLoop);
		SetRotation(GetRotation() + 180 * dt);
	}
	return pos;
}
