#include "Gameplay.h"

Gameplay::Gameplay()
{
	mainThemeId = AUDIO.LoadMusic("Resources/Audio/MainTheme.mp3");
	AUDIO.PlayMusic(mainThemeId);

	stageCompletedId = AUDIO.LoadClip("Resources/Audio/StageCompleted.mp3");

	ship = new ShipBackGround();
	player = new Player(ship);

	remainingWaves = LEVELLOADER.LoadLevel("Resources/Levels/stage_0.xml", player);

	objects.push_back(new SeaBackground());
	objects.push_back(new SeaBackground(RENDERER.GetSizeWindow().y));
	objects.push_back(ship);
	objects.push_back(player);  

	// TEXT OBJECTS
		// SCORE
	ui.push_back(SCORE.GetScoreUI());
		// NAME PLAYER
	ui.push_back(new TextObject("Player 01", 15, { 255, 255, 255 },
		new Transform(Vector2(10, 5), 0, Vector2(1, 1), Vector2(15, 15), false),
		"Resources/PixelPowerline-11Mg.ttf"));
		// LIVES PLAYER
	ui.push_back(LIVES_GAME.GetLivesUI());

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

	for (int i = remainingWaves.size() - 1; i >= 0; i--)
	{
		if (remainingWaves[i].WaveDone())
		{
			remainingWaves.erase(remainingWaves.begin() + i); 
			continue; 
		}
		 remainingWaves[i].Update(dt);
	}
	if (remainingWaves.size() == 1)
	{
		ship->Finished();
	}

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
	timeToSpawnIsland = 20 + rand() % 20;

	int maxX = RENDERER.GetSizeWindow().x;
	int maxY = RENDERER.GetSizeWindow().y;

	float posX = 24 + rand() % (maxX - 208);
	float posY = rand() % (maxY - 88) + 8;

	Vector2 pos = Vector2(posX, posY);
	IslandBackground* island = new IslandBackground(posX, posY);

	objects.insert(objects.begin() + 2, island);
}
