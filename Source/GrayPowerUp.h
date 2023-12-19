#pragma once
#include "PowerUp.h"

/**
* An assisting plane is added to each side of the player.
* Each assisting plane fires one missile when the player shoots.If an assisting plane 
* collides with an enemy, the assisting plane is destroyed, but the player isn't harmed.
*/

class GrayPowerUp : public PowerUp
{
public:
	GrayPowerUp(Player* p)
		:PowerUp(p)
	{
		renderer = new ImageRenderer(transform, Vector2(40, 140), Vector2(13, 10));
	}

	virtual bool IsPlayer(Object* other) override
	{
		if (dynamic_cast<Player*>(other))
		{
			player->AddSupportPlanes();
			Destroy();
			return true;
		}
		return false;
	}
};