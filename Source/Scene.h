#pragma once
#include <vector>
#include "Object.h"
#include "TextObject.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Spawner.h"

//Scenes names
#define GAMEPLAY "Gameplay"
#define MAIN "Main Menu"
#define SPLASH "SplashScreen"
#define RANKING "Ranking"

class Scene
{
protected:
	std::vector<Object*> ui; 
	std::vector<Object*> objects;

	bool isFinished; 
	std::string nextScene; 

public:
	Scene() = default; 
	virtual void OnEnter() = 0; 
	virtual std::string OnExit(); 
	virtual void Update(float dt); 
	virtual void Render(); 

	inline bool GetIsFinished() { return isFinished; }
};

