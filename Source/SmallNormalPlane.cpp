#include "SmallNormalPlane.h"

SmallNormalPlane::SmallNormalPlane()
	: EnemyPlane(1, 50)
{
	fireTime = 1.00f;
	lastFireTime = 0.0f;

	// TRANSFORM
	transform.position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.5);
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
}

void SmallNormalPlane::UpdateMovementPattern(float dt)
{

}