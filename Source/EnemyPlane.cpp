#include "EnemyPlane.h"

// OnCollisionEnter
#include "PlayerBullet.h"

EnemyPlane::EnemyPlane(int hp, int score)
	: health(hp),  score(score)
{
	isPendingDestroy = false; 

	iFrames = 1.0f; 
	lastIFrames = iFrames; 
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
		SPAWNER.SpawnObject(new EnemyBullet(transform.position));
	}
}

void EnemyPlane::OnCollisionEnter(Object* other)
{
	if (rb->CheckCollision(other->GetRigidBody()))
	{
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
			Destroy();
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
