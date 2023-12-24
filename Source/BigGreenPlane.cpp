#include "BigGreenPlane.h"

BigGreenPlane::BigGreenPlane(Transform* _playerTransform)
	: EnemyPlane(32, 4400, _playerTransform)
{
	pixelsPorSecond = Vector2(0, 1);

	timeToStop = 4.0f;
	timeShooting = 3.0f;

	// TRANSFORM
	transform = new Transform();
	transform->size = Vector2(48, 48);
	transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.75, RENDERER.GetSizeWindow().y + transform->size.y * 0.5);
	transform->angle = 0.0f;
	transform->scale = Vector2(2.0f, 2.0f);

	// RENDER
	renderers.emplace("Idle", new ImageRenderer(transform, Vector2(7, 323), Vector2(63, 48)));
	DeathAnimation();
	renderer = renderers["Idle"];

	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void BigGreenPlane::Update(float dt)
{
	EnemyPlane::Update(dt); 
	movementTime += dt;

	if (isAlive)
		UpdateMovementPattern(dt);
	else
		DeathState(); 
}

void BigGreenPlane::UpdateMovementPattern(float dt)
{
	Vector2 direction = Vector2(); 

	if (movementTime >= timeToStop)
	{
		Shoot();
		if (movementTime >= (timeToStop + timeShooting))
			movementTime = 0.0f;
	}
	else
		direction = direction - pixelsPorSecond;

	transform->position = transform->position + direction;
}

void BigGreenPlane::DeathAnimation()
{
	std::vector<Vector2> deathDeltas{
		Vector2(66, 0),
		Vector2(66 * 2, 0),
		Vector2(66 * 3, 0),
		Vector2(0, 59),
		Vector2(66, 59),
		Vector2(66 * 2, 59)
	};
	renderers.emplace("Death", new AnimatedImageRenderer(transform, Vector2(7, 323), Vector2(63, 48), deathDeltas, false, 10));
}