#include "Gameplay.h"

Gameplay::Gameplay()
{
	objects.push_back(new WaterBackGround());
	objects.push_back(new WaterBackGround(RENDERER.GetSizeWindow().x));
	objects.push_back(new Player());  

	sfxID = AUDIO.LoadClip("Resources/Audio/discord-notification.mp3");

	nextScene = MAIN;
}

void Gameplay::OnEnter()
{
}

void Gameplay::Render()
{
	Scene::Render(); 
}

void Gameplay::Update(float dt)
{
	Scene::Update(dt); 

	isFinished = IM.CheckKeyState(SDLK_e, PRESSED);
}

void Gameplay::SpawnIsland()
{
	float maxX = RENDERER.GetSizeWindow().x;
	float posX = rand() % (maxX -1) + 1;
	float posY;

	Vector2 pos;

	objects.insert(objects.begin() + 2, new IslandBackground());
}
