#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(Vector2 pos, Player* _playerReference)
{
	player = _playerReference;

	isPendingDestroy = false;

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

	//Calculate direction of the bullet
	directionToShoot = player->GetPosition() - transform.position;

	
	speed = directionToShoot;
	speed.Normalize();

	speed = speed * 160;
}

void EnemyBullet::Update(float dt)
{
	Object::Update(dt);

	rb->SetVeclocity(speed);

	// Out of window
	if (transform.position.y > RENDERER.GetSizeWindow().y + transform.size.y
		|| transform.position.y < -transform.size.y
		|| transform.position.x < -transform.size.x
		|| transform.position.x > RENDERER.GetSizeWindow().x + transform.size.x)
		Destroy();
}
