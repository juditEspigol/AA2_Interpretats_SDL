#pragma once
#include "PowerUp.h"

/**
* Powers up the main weapon: it fires 4 missiles at once instead of 2.
*/

class GreenPowerUp : public PowerUp
{
public:
	GreenPowerUp(Player* p)
		:PowerUp(p)
	{
		renderer = new ImageRenderer(transform, Vector2(74, 140), Vector2(13, 10));
		scoreToGive = 1500;
	}

	virtual bool IsPlayer(Object* other) override
	{
		if (dynamic_cast<Player*>(other))
		{
			player->EnableDoubleFire(); 
			Destroy();
			if(player->GetDoubleFireEnabled())
				GiveScore();
			return true;
		}
		return false;
	}
};