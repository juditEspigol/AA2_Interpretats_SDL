#pragma once
#include "GameObject.h"
#include "PlayerBullet.h"
#include "Spawner.h"

class SupportPlane : public GameObject
{
private:
	bool isRight; 
	Vector2 offset;

	bool isLocated;

public:
	SupportPlane(bool right, Vector2 pos);

	void Update(float dt) override;
	void LocatePlane(Vector2 playerPosition, float dt);

	virtual void OnCollisionEnter(Object* other) override;
	bool IsEnemyPlane(Object* other);
	bool IsEnemyBullet(Object* other);

	void Shoot();
};