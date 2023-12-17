#include "SupportPlane.h"

// OnCollisionEnter
#include "EnemyBullet.h"
#include "EnemyPlane.h"

SupportPlane::SupportPlane(Vector2 offset, Vector2 pos)
	:offset(offset)
{
	isPendingDestroy = false;

	// TRANSFORM
	transform.position = pos;
	transform.angle = 0.0f;
	transform.scale = Vector2(1.5f, 1.5f);
	transform.size = Vector2(18, 16);
	// RENDER
	renderer = new ImageRenderer(&transform, Vector2(9, 84), Vector2(18, 10));
	// RIGID BODY 
	rb = new RigidBody(&transform);
	Vector2 topLeft = transform.position - transform.size / 2;
	rb->AddCollision(new AABB(topLeft, transform.size));
	rb->SetLinearDrag(7);
}

void SupportPlane::Update(float dt)
{
	GameObject::Update(dt); 
}

void SupportPlane::OnCollisionEnter(Object* other)
{
	if (rb->CheckCollision(other->GetRigidBody()))
	{
		if (IsEnemyPlane(other))
			return;
		if (IsEnemyBullet(other))
			return;
	}
}

bool SupportPlane::IsEnemyPlane(Object* other)
{
	/*if (dynamic_cast<EnemyPlane*>(other))
	{
		Destroy();
		return true;
	}*/

	return false;
}
bool SupportPlane::IsEnemyBullet(Object* other)
{
	/*if (dynamic_cast<EnemyBullet*>(other))
	{
		Destroy();
		return true;
	}*/
	return false;
}

void SupportPlane::Shoot()
{
	SPAWNER.SpawnObject(new PlayerBullet(transform.position));
}
