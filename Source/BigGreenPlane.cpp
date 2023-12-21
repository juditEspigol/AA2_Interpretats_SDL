#include "BigGreenPlane.h"

BigGreenPlane::BigGreenPlane(Transform* _playerTransform)
	: EnemyPlane(32, 4400, _playerTransform)
{
	fireTime = 1.00f;
	lastFireTime = 0.0f;

	// TRANSFORM
	transform = new Transform();
	transform->size = Vector2(48, 48);
	transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.75, RENDERER.GetSizeWindow().y + transform->size.y * 0.5);
	transform->angle = 0.0f;
	transform->scale = Vector2(2.0f, 2.0f);
	// RENDER
	renderer = new ImageRenderer(transform, Vector2(7, 323), Vector2(63, 48));
	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void BigGreenPlane::Update(float dt)
{
	EnemyPlane::Update(dt); 

	UpdateMovementPattern(dt); 
}

void BigGreenPlane::UpdateMovementPattern(float dt)
{
	Vector2 direction = Vector2(); 

	if (movementTime <= stopTime)
	{
		direction = direction - pixelsPorSecond;
		if (movementTime >= stopTime + timeShooting)
		{
			movementTime = 0;
			Shoot(); 
		}
	}
	transform->position = transform->position + direction;
}