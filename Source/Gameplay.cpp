#include "Gameplay.h"

Gameplay::Gameplay()
{
	player = new Player();

	Wave newWave(5, WaveType::SmallNormal, player->GetTransform());

	remainingWaves.push_back(newWave);

	objects.push_back(new SeaBackground());
	objects.push_back(new SeaBackground(RENDERER.GetSizeWindow().y));
	objects.push_back(player);  

	//objects.push_back(new SmallRedPlane(false, true));
	//objects.push_back(new MediumYellowPlane(false));
	//objects.push_back(new MediumYellowPlane(true));

	objects.push_back(new GreenPowerUp());


	// TEXT OBJECTS
		// SCORE
	ui.push_back(SCORE.GetScoreUI());
		// NAME PLAYER
	ui.push_back(new TextObject("Player 01", 15, { 255, 255, 255 },
		new Transform(Vector2(10, 5), 0, Vector2(1, 1), Vector2(15, 15), false),
		"Resources/PixelPowerline-11Mg.ttf"));
		// LIVES PLAYER
	ui.push_back(new TextObject("000", 15, { 255, 0, 0 },
		new Transform(Vector2(10, RENDERER.GetSizeWindow().y - 30), 0, Vector2(1, 1), Vector2(15, 15), false),
		"Resources/PixelPowerline-11Mg.ttf"));

	sfxID = AUDIO.LoadClip("Resources/Audio/discord-notification.mp3");

	nextScene = MAIN;

	timeToSpawnIsland = 20 + rand() % 20;
	currentTimeToSpawnIsland = 0;
	sizeRemainingWaves = remainingWaves.size();
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

	for (int i = 0; i < sizeRemainingWaves; i++)
	{
		 remainingWaves[i].Update(dt);
	}

	//remainingWaves[0].Update(dt);

	isFinished = IM.CheckKeyState(SDLK_e, PRESSED);

	/*if (IM.CheckKeyState(SDLK_SPACE, PRESSED))
		AUDIO.PlayClip(sfxID);*/

	currentTimeToSpawnIsland += dt;

	if (currentTimeToSpawnIsland >= timeToSpawnIsland)
	{
		currentTimeToSpawnIsland = 0;
		SpawnIsland();
	}
}

void Gameplay::SpawnIsland()
{
	timeToSpawnIsland = 20 + rand() % 20;

	int maxX = RENDERER.GetSizeWindow().x;
	int maxY = RENDERER.GetSizeWindow().y;

	float posX = 24 + rand() % (maxX - 208);
	float posY = rand() % (maxY - 88) + 8;

	Vector2 pos = Vector2(posX, posY);
	IslandBackground* island = new IslandBackground(posX, posY);

	objects.insert(objects.begin() + 2, island);
}
