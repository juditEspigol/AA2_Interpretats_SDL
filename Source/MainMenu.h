#pragma once
#include "Scene.h"

// AGREGATTION
#include "Button.h"

class MainMenu : public Scene
{
private:
public:
	MainMenu(); 
	virtual void OnEnter() override;
	virtual void Update(float dt) override;
};

