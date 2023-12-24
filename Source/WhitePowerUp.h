#pragma once
#include "PowerUp.h"
#include "EnemyPlane.h"

/**
* Destroys all spawned enemies.
*/

class WhitePowerUp : public PowerUp
{
private:
	bool activated; 

public:
	WhitePowerUp(Player* p)
		:PowerUp(p), activated(false)
	{
		renderer = new ImageRenderer(transform, Vector2(6, 140), Vector2(13, 10));
		scoreToGive = 2000;
		powerUpID = AUDIO.LoadClip("Resources/Audio/PowerUp3.mp3");
	}

	void OnCollisionEnter(Object* other) override
	{
		PowerUp::OnCollisionEnter(other); 

		if (activated && dynamic_cast<EnemyPlane*>(other))
		{
			other->Destroy();
		}
	}

	virtual bool IsPlayer(Object* other) override
	{
		if (dynamic_cast<Player*>(other))
		{
			activated = true;
			Destroy();
			GiveScore();
			return true;
		}
		return false;
	}
};