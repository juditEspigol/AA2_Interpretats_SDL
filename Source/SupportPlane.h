#pragma once
#include "GameObject.h"
#include "PlayerBullet.h"
#include "Spawner.h"

class SupportPlane : public GameObject
{
private:
	Vector2 offset; 

public:
	SupportPlane(Vector2 offset, Vector2 pos);

	void Update(float dt) override; 
	virtual void OnCollisionEnter(Object* other) override;

	bool IsEnemyPlane(Object* other);
	bool IsEnemyBullet(Object* other);

	void Shoot();

	inline Vector2 GetOffset() const { return offset; }
};