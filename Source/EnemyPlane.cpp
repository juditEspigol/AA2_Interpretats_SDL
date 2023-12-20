#include "EnemyPlane.h"
#include "ScoreManager.h"

// OnCollisionEnter
#include "PlayerBullet.h"

EnemyPlane::EnemyPlane(int _hp, int _score, Transform* _playerTransform)
	: health(_hp),  score(_score)
{
	isPendingDestroy = false; 
	outOfWindow = false;

	iFrames = 1.0f; 
	lastIFrames = iFrames; 

	playerTransform = _playerTransform;
}

void EnemyPlane::Update(float dt)
{
	Object::Update(dt);

	lastIFrames += dt;  

	lastFireTime += dt;  
	Shoot(); 
}

void EnemyPlane::Shoot()
{
	if (lastFireTime >= fireTime)
	{
		lastFireTime = 0;

		SPAWNER.SpawnObject(new EnemyBullet(transform->position, playerTransform->position));
	}
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

void EnemyPlane::GetDamage(const int amount)
{
	if (lastIFrames >= iFrames)
	{
		lastIFrames = 0;
		health -= amount;

		if (health <= 0)
		{
			Destroy();
		}
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
		outOfWindow = true; 
		Destroy();
		return true;
	}
	return false;
}
