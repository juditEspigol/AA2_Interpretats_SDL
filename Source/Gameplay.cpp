#include "Gameplay.h"

Gameplay::Gameplay()
{
	objects.push_back(new WaterBackGround());
	objects.push_back(new WaterBackGround(RENDERER.GetSizeWindow().x));
	objects.push_back(new Player());  

	sfxID = AUDIO.LoadClip("Resources/Audio/discord-notification.mp3");

	nextScene = MAIN;

	timeToSpawnIsland = 11 + rand() % 7;
	currentTimeToSpawnIsland = 0;
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

	currentTimeToSpawnIsland += dt;

	if (currentTimeToSpawnIsland >= timeToSpawnIsland)
	{
		currentTimeToSpawnIsland = 0;
		SpawnIsland();
	}
}

void Gameplay::SpawnIsland()
{
	timeToSpawnIsland += 10;

	int maxX = RENDERER.GetSizeWindow().x;
	int maxY = RENDERER.GetSizeWindow().y;

	float posX = 24 + rand() % (maxX - 208);
	float posY = rand() % (maxY - 88) + 8;

	Vector2 pos = Vector2(posX, posY);
	IslandBackground* island = new IslandBackground(posX, posY);

	objects.insert(objects.begin() + 2, island);
}
