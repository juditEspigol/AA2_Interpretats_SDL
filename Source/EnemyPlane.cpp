#include "EnemyPlane.h"

void EnemyPlane::Shoot()
{
}

EnemyPlane::EnemyPlane(int hp, int score)
	: health(hp),  score(score)
{
	isPendingDestroy = false; 
}
