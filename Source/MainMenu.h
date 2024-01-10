#pragma once
#include "Scene.h"

// AGREGATTION
#include "Button.h"

class MainMenu : public Scene
{
private:
	bool enableAudio; 

public:
	MainMenu(); 
	virtual void OnEnter() override;
	virtual void Update(float dt) override;
};

