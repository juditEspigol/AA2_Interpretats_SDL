#pragma once
#include "Scene.h"

class SplashScreen : public Scene
{
private:
	float timeToWait; 
	float timeWaiting; 

public:
	SplashScreen();
	virtual void OnEnter() override;
	virtual void Update(float dt) override;
};
