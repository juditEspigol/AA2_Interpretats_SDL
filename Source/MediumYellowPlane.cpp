#include "MediumYellowPlane.h"

MediumYellowPlane::MediumYellowPlane()
	: EnemyPlane(12, 2530)
{
	fireTime = 1.00f;
	lastFireTime = 0.0f;

	// TRANSFORM
	transform.position = Vector2(RENDERER.GetSizeWindow().x * 0.25, RENDERER.GetSizeWindow().y * 0.5);
	transform.angle = 0.0f;
	transform.scale = Vector2(2.0f, 2.0f);
	transform.size = Vector2(32, 32);
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
}

void MediumYellowPlane::UpdateMovementPattern(float dt)
{

}