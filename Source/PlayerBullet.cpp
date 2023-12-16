#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(Vector2 pos)
{
	isPendingDestroy = false;
	speed = Vector2(0, -300); 
	// TRANSFORM
	transform.position = Vector2(pos.x, pos.y - 5);
	transform.angle = 0.0f;
	transform.scale = Vector2(1.0f, 1.0f);
	transform.size = Vector2(4, 16);
	// RENDER
	renderer = new ImageRenderer(&transform, Vector2(92, 84), Vector2(2, 10));
	// RIGID BODY
	rb = new RigidBody(&transform);
	Vector2 topLeft = transform.position - transform.size / 2;
	rb->AddCollision(new AABB(topLeft, transform.size));
}

void PlayerBullet::Update(float dt)  
{
	rb->SetVeclocity(speed);
	rb->Update(dt);

	if (transform.position.y <= 0)
		Destroy();
}