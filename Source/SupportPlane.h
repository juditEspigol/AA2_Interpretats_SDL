#pragma once
#include "GameObject.h"
#include "PlayerBullet.h"
#include "Spawner.h"

class SupportPlane : public GameObject
{
private:
	bool isRight; 
	bool isLocated; 
	Vector2 offset; 

public:
	SupportPlane(bool right, Vector2 pos);

	void Update(float dt) override; 
	virtual void OnCollisionEnter(Object* other) override;

	bool IsEnemyPlane(Object* other);
	bool IsEnemyBullet(Object* other);

	void Shoot();

	inline Vector2 GetOffset() const { return offset; }
	inline bool GetIsLocated() { return isLocated; }

	void LocatePlane(Vector2 playerPosition, float dt)
	{
		Vector2 positionToGo = playerPosition - offset;

		if (isLocated)
		{
			transform->position = positionToGo;
		}
		else
		{
			Vector2 direction = positionToGo - transform->position;
			float pixelsPorSecond = 4;
			Vector2 force = Vector2();

			if (direction.Magnitude() <= 10) // near 
			{
				isLocated = true;
				SetRotation(0);
			}
			else
			{
				//VERTICAL
				if (transform->position.y < positionToGo.y) // support up, player down
					force.y += pixelsPorSecond;
				if (transform->position.y > positionToGo.y) // support down, player up
					force.y -= pixelsPorSecond;
				//HORITZONTAL
				if (transform->position.x < positionToGo.x) // support left, player right
					force.x += pixelsPorSecond;
				if (transform->position.x > positionToGo.x) // support right, player left
					force.x -= pixelsPorSecond;

				transform->position = transform->position + force;

				//SPINNING
				SetRotation(GetRotation() + (360 * dt));
			}
		}
	}
};