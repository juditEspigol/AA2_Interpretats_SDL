#pragma once
#include <cassert>
#include <vector>

// Managers
#include "RenderManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Spawner.h"

// Objects childs
#include "TextObject.h"
#include "GameObject.h"

// Scenes names
#define GAMEPLAY "Gameplay"
#define MAIN "Main Menu"
#define SPLASH "Splash Screen"
#define RANKING "Ranking"
#define GAMEOVER "Game Over"

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

