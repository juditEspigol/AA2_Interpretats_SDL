#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(Vector2 pos)
{
	isPendingDestroy = false;
	speed = Vector2(0, 300);

	// TRANSFORM
	transform.size = Vector2(4, 16);
	transform.position = Vector2(pos.x, pos.y + transform.size.y * 0.5);
	transform.angle = 0.0f;
	transform.scale = Vector2(1.0f, 1.0f);
	// RENDER
	renderer = new ImageRenderer(&transform, Vector2(75, 92), Vector2(4, 4));
	// RIGID BODY
	rb = new RigidBody(&transform);
	Vector2 topLeft = transform.position - transform.size / 2;
	rb->AddCollision(new AABB(topLeft, transform.size));
}

void EnemyBullet::Update(float dt)
{
	rb->SetVeclocity(speed);
	rb->Update(dt);

	// Out of window
	if (transform.position.y >= RENDERER.GetSizeWindow().y)
		Destroy();
}
