#include "MediumYellowPlane.h"

MediumYellowPlane::MediumYellowPlane(bool _isRight, Transform* _playerTransform)
	: EnemyPlane(12, 2530, _playerTransform), isRight(_isRight)
{
	fireTime = 1.00f;
	lastFireTime = 0.0f;
	startLoop = 1.5f; 
	pixelsPorSecond = Vector2(0, 3); 
	radiusLoop = Vector2(7, 3);

	// TRANSFORM
	transform = new Transform();
	transform->size = Vector2(32, 32);
	if(isRight)
		transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5 - (18.7248 * radiusLoop.x), -transform->size.y * 0.75);
	else
		transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5 + (18.7248 * radiusLoop.x), -transform->size.y * 0.75);
	transform->angle = 0.0f;
	transform->scale = Vector2(2.0f, 2.0f);

	// RENDER
	renderers.emplace("Idle", new ImageRenderer(transform, Vector2(7, 501), Vector2(31, 23)));
	DeathAnimation();
	renderer = renderers["Idle"];

	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void MediumYellowPlane::Update(float dt)
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

void MediumYellowPlane::UpdateMovementPattern(float dt)
{
	Vector2 direction = pixelsPorSecond;

	// Check if start loop
	if (movementTime <= startLoop) // GOING DOWN
	{
		direction.y *= 1; 
	}
	else if (movementTime >= startLoop && movementTime <= (startLoop + 3.0f)) // 2s = 1 loop
	{
		if (isRight)
			direction = Loop(dt, 1, -1); 
		else
			direction = Loop(dt, -1, -1);
	}
	else // GOING UP
	{
		direction.y *= -1;
	}

	transform->position = transform->position + direction;
}

Vector2 MediumYellowPlane::Loop(float dt, int cosSigne, int sinSigne)
{
	Vector2 pos = Vector2();
	pos = Vector2(cosSigne * cos(movementTime * M_PI) * radiusLoop.x,
		sinSigne * sin(movementTime * M_PI) * radiusLoop.y);
	SetRotation(GetRotation() - cosSigne * 180 * dt);

	return pos;
}

void MediumYellowPlane::DeathAnimation()
{
	std::vector<Vector2> deathDeltas{
		Vector2(0, 0),
		Vector2(20, 0),
		Vector2(20 * 2, 0),
		Vector2(20 * 3, 0),
		Vector2(20 * 4, 0),
		Vector2(20 * 5, 0)
	};
	renderers.emplace("Death", new AnimatedImageRenderer(transform, Vector2(157, 80), Vector2(20, 20), deathDeltas, false, 10));
}