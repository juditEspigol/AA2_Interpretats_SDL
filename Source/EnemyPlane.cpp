#include "EnemyPlane.h"
#include "ScoreManager.h"

// OnCollisionEnter
#include "PlayerBullet.h"

EnemyPlane::EnemyPlane(int _hp, int _score, Transform* _playerTransform)
	: health(_hp),  score(_score), playerTransform(_playerTransform)
{
	isPendingDestroy = false; 

	fireTime = 1.00f;
	lastFireTime = 0.0f;
	speed = Vector2(12, 22);

	movementTime = 0.0f; 
}

void EnemyPlane::Update(float dt)
{
	Object::Update(dt);

	lastFireTime += dt;  
	movementTime += dt;
}

void EnemyPlane::Shoot()
{
	if (lastFireTime >= fireTime)
	{
		lastFireTime = 0;
		SPAWNER.SpawnObject(new EnemyBullet(transform->position, playerTransform->position));
	}
}

void EnemyPlane::GetDamage(const int amount)
{
	health -= amount;

	if (health <= 0 && !isPendingDestroy)
		Destroy();
}

void EnemyPlane::OnCollisionEnter(Object* other)
{
	if (rb->CheckCollision(other->GetRigidBody()))
	{
		if (IsOutOfWindow())
			return;

		if (IsPlayerBullet(other))
			return;
	}
}
bool EnemyPlane::IsPlayerBullet(Object* other)
{
	if (dynamic_cast<PlayerBullet*>(other))
	{
		GetDamage(1);
		other->Destroy();
		return true;
	}
	return false;
}
bool EnemyPlane::IsOutOfWindow()
{
	if (transform->position.y > RENDERER.GetSizeWindow().y + transform->size.y
		|| transform->position.y < -transform->size.y
		|| transform->position.x < -transform->size.x
		|| transform->position.x > RENDERER.GetSizeWindow().x + transform->size.x)
	{
		isPendingDestroy = true;
		return true;
	}
	return false;
}
