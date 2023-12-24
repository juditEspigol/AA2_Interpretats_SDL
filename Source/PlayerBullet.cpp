#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(Vector2 pos)
{
	isPendingDestroy = false;
	speed = Vector2(0, -500); 

	// TRANSFORM
	transform = new Transform();
	transform->size = Vector2(4, 16);
	transform->position = Vector2(pos.x, pos.y - transform->size.y * 2);
	transform->angle = 0.0f;
	transform->scale = Vector2(1.0f, 1.0f);
	// RENDER
	renderer = new ImageRenderer(transform, Vector2(92, 84), Vector2(2, 10));
	// RIGID BODY
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
}

void PlayerBullet::Update(float dt)  
{
	rb->SetVeclocity(speed);
	rb->Update(dt);

	// Out of window
	if (transform->position.y <= 0)
		Destroy();
}
