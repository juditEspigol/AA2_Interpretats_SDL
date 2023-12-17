#include "BigGreenPlane.h"

BigGreenPlane::BigGreenPlane(Player* playerReference)
	: EnemyPlane(32, 4400, playerReference)
{
	fireTime = 1.00f;
	lastFireTime = 0.0f;

	// TRANSFORM
	transform.position = Vector2(RENDERER.GetSizeWindow().x * 0.75, RENDERER.GetSizeWindow().y * 0.5);
	transform.angle = 180.0f;
	transform.scale = Vector2(2.0f, 2.0f);
	transform.size = Vector2(48, 48);
	// RENDER
	renderer = new ImageRenderer(&transform, Vector2(7, 323), Vector2(63, 48));
	// RIGID BODY 
	rb = new RigidBody(&transform);
	Vector2 topLeft = transform.position - transform.size / 2;
	rb->AddCollision(new AABB(topLeft, transform.size));
	rb->SetLinearDrag(7);
}

void BigGreenPlane::Update(float dt)
{
	EnemyPlane::Update(dt);
}

void BigGreenPlane::UpdateMovementPattern(float dt)
{

}