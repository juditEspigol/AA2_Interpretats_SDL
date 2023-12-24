#include "Gameplay.h"

Gameplay::Gameplay()
{
	currentState = GAME;

	currentKeyLevel = 0;
	ship = new ShipBackGround();
	player = new Player(ship);

	levelLoader = LevelLoader(player);

	mainThemeId = AUDIO.LoadMusic("Resources/Audio/MainTheme.mp3");
	AUDIO.PlayMusic(mainThemeId);

	stageCompletedId = AUDIO.LoadClip("Resources/Audio/StageCompleted.mp3");

	remainingWaves = levelLoader.LoadLevel(currentKeyLevel);

	objects.push_back(new SeaBackground());
	objects.push_back(new SeaBackground(RENDERER.GetSizeWindow().y));
	objects.push_back(ship);
	objects.push_back(player);  

	// TEXT OBJECTS
		//PAUSED
	ui.push_back(new TextObject("  ", 30, { 255, 255, 255 },
		new Transform(RENDERER.GetSizeWindow() * 0.5, 0, Vector2(1, 1), Vector2(30, 30), true),
		"Resources/PixelPowerline-11Mg.ttf"));
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
	switch (currentState)
	{
	case GAME:

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

	currentTimeToSpawnIsland += dt;

		if (currentTimeToSpawnIsland >= timeToSpawnIsland)
		{
			currentTimeToSpawnIsland = 0;
			SpawnIsland();
		}

		if (player->IsPlayerPaused())
			currentState = FINISH_STATE; 

		if (LIVES_GAME.GetLives() == 0)
			currentState = GAME_OVER; 

		if (IM.CheckKeyState(SDLK_p, PRESSED) || IM.CheckKeyState(SDLK_ESCAPE, PRESSED))
		{
			currentState = PAUSE;
			ui[0]->GetRenderer()->NewText("PAUSED");
		}

		break;

	case PAUSE:

		if (IM.CheckKeyState(SDLK_p, PRESSED) || IM.CheckKeyState(SDLK_ESCAPE, PRESSED))
		{
			currentState = GAME;
			ui[0]->GetRenderer()->NewText("  ");
		}

		break;
	case FINISH_STATE:

		player->Update(dt); 


		if (!player->IsPlayerPaused())
		{
			if (currentKeyLevel == 2)
				currentKeyLevel = 0;
			else
				currentKeyLevel++;

			remainingWaves = levelLoader.LoadLevel(currentKeyLevel);
			currentState = GAME; 
		}

		break;
	case GAME_OVER:

		levelLoader.ReadAllLevels(player);

		LIVES_GAME.Reset();
		SCORE.Reset();

		for (int i = objects.size() - 1; i >= 0; i--)
		{
			if (dynamic_cast<SeaBackground*>(objects[i]) || 
				dynamic_cast<ShipBackGround*>(objects[i]) ||
				dynamic_cast<Player*>(objects[i]))
				continue; 

			delete objects[i];
			objects.erase(objects.begin() + i);
		}
		

		currentKeyLevel = 0;
		remainingWaves = levelLoader.LoadLevel(currentKeyLevel);

		ship->Reset(); 
		player->Reset(); 

		currentState = GAME; 

		break;
	default:
		break;
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
