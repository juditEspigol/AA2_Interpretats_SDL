#include "EnemyPlane.h"

EnemyPlane::EnemyPlane(int _hp, int _score, Transform* _playerTransform)
	: health(_hp),  score(_score), playerTransform(_playerTransform)
{
	isPendingDestroy = false; 
	isAlive = true; 
	shootId = AUDIO.LoadClip("Resources/Audio/EnemyShoot.mp3");
	bulletId = AUDIO.LoadClip("Resources/Audio/BulletCollision.mp3");

	fireTime = 1.00f;
	lastFireTime = 0.0f;

	movementTime = 0.0f; 
}

void EnemyPlane::Update(float dt)
{
	GameObject::Update(dt);

	lastFireTime += dt;  

	if (renderer == renderers["Death"] && renderer->LastFrame())
		Destroy(); 
}

void EnemyPlane::Shoot()
{
	if (lastFireTime >= fireTime)
	{
		lastFireTime = 0;
		AUDIO.PlayClip(shootId);
		SPAWNER.SpawnObject(new EnemyBullet(transform->position, playerTransform->position));
	}
}

void EnemyPlane::DeathState()
{	
	Destroy();
}

void EnemyPlane::GetDamage(const int amount)
{
	health -= amount;

	if (health <= 0 )
		isAlive = false; 
}

void EnemyPlane::OnCollisionEnter(Object* other)
{
	if (rb->CheckCollision(other->GetRigidBody()))
	{
		if (IsOutOfWindow())
			return;

		if (IsPlayerBullet(other))
		{
			AUDIO.PlayClip(bulletId);
			return;
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
		isPendingDestroy = true;
		return true;
	}
	return false;
}
