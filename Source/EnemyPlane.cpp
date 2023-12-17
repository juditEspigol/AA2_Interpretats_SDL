#include "EnemyPlane.h"
#include "ScoreManager.h"

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

	if (transform.position.y > RENDERER.GetSizeWindow().y + transform.size.y
		|| transform.position.y < -transform.size.y 
		|| transform.position.x < -transform.size.x
		|| transform.position.x > RENDERER.GetSizeWindow().x + transform.size.x)
	{
		Destroy();
	}
}

void EnemyPlane::Shoot()
{
	if (lastFireTime >= fireTime)
	{
		lastFireTime = 0;
		SPAWNER.SpawnObject(new EnemyBullet(transform.position, rb->GetVelocity()));
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
		{
			SCORE.AddScore(score); 
			SCORE.GetScoreUI()->GetRenderer()->NewText(std::to_string(SCORE.GetScore())); 
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
