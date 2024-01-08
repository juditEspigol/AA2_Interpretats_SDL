#pragma once
#include <vector>
#include "Object.h"
#include "TextObject.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Spawner.h"

//Scenes names
#define GAMEPLAY "Gameplay"
#define MAIN "Main Menu"
#define SPLASH "Splash Screen"
#define RANKING "Ranking"

class Scene
{
protected:
	std::vector<TextObject*> ui; 
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

