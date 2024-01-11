#include "Gameplay.h"

Gameplay::Gameplay()
{
	isFinished = false; 
	nextScene = MAIN; 
	currentState = GAME;

	currentKeyLevel = 0;
	ship = new ShipBackGround();
	player = new Player(ship);

	levelLoader = LevelLoader(player);

	mainThemeId = AUDIO.LoadMusic("Resources/Audio/MainTheme.mp3");
	AUDIO.PlayMusic(mainThemeId);

	stageCompletedId = AUDIO.LoadClip("Resources/Audio/StageCompleted.mp3");

	remainingWaves = levelLoader.LoadLevel(currentKeyLevel);
	SCORE.planesPerStage = GetPlanesPerStage();

	objects.push_back(new SeaBackground());
	objects.push_back(new SeaBackground(RENDERER.GetSizeWindow().y));
	objects.push_back(ship);
	objects.push_back(player);  

	// TEXT OBJECTS
		// PAUSED OBJECT[0]!!!!!!
	ui.push_back(new TextObject("  ", 30, { 255, 255, 255 },
		new Transform(RENDERER.GetSizeWindow() * 0.5, 0, Vector2(1, 1), Vector2(30, 30), true),
		"Resources/PixelPowerline-11Mg.ttf"));
		// NEXT LEVEL OBJECT[1]!!!!!!
	ui.push_back(new TextObject("  ", 12, { 255, 255, 255 },
		new Transform(RENDERER.GetSizeWindow() * 0.5, 0, Vector2(1, 1), Vector2(30, 30), true),
		"Resources/PixelPowerline-11Mg.ttf"));
		// ROLLS!!!!
	ui.push_back(new TextObject("R: " + std::to_string(player->GetAvaliableRolls()), 15, {255, 255, 255},
		new Transform(Vector2(RENDERER.GetSizeWindow().x - 70, RENDERER.GetSizeWindow().y - 30), 0, Vector2(1, 1), Vector2(15, 15), false),
		"Resources/PixelPowerline-11Mg.ttf"));
		// SCORE
	ui.push_back(SCORE.GetScoreUI());
		// NAME PLAYER
	ui.push_back(new TextObject("1UP", 15, { 255, 255, 255 },
		new Transform(Vector2(35, 5), 0, Vector2(1, 1), Vector2(15, 15), false),
		"Resources/PixelPowerline-11Mg.ttf"));
		// LIVES PLAYER
	ui.push_back(LIVES_GAME.GetLivesUI());


	buttons.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 360), "RESUME"));
	buttons.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 440), "BACK TO MAIN"));


	timeToSpawnIsland = 20 + rand() % 20;
	currentTimeToSpawnIsland = 0;
	sizeRemainingWaves = remainingWaves.size();
}

void Gameplay::OnEnter()
{
	RENDERER.SetWindowsColor(0, 95, 205);
	currentState = GAME; 
	currentTimeToSpawnIsland = 0; 
	SCORE.Reset(); 
	LIVES_GAME.Reset();
	ResetAll(); 
}

void Gameplay::Render()
{
	if (currentState == HIT)
		return; 
	
	Scene::Render(); 

	if (currentState == PAUSE)
	{
		for (Button* button : buttons)
			button->Render();
	}
}

void Gameplay::Update(float dt)
{

	CheckCurrentState(dt);

	switch (currentState)
	{
	case GAME:
		Scene::Update(dt); 
		GameState(dt); 
		break;

	case PAUSE:
		GamePaused(dt); 
		break;

	case FINISH_STATE:
		player->Update(dt);
		FinishState(dt); 
		break;

	case HIT:
		player->Update(dt);
		HitState(dt); 
		break; 

	case GAME_OVER:
		nextScene = GAMEOVER; 
		isFinished = true; 
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

void Gameplay::CheckCurrentState(float dt)
{
	switch (currentState)
	{
	case GAME:

		if (player->IsPlayerPaused())
			ChangeCurrentState(FINISH_STATE);

		if (player->PlayerHitted())
			ChangeCurrentState(HIT);

		if (LIVES_GAME.GetLives() == 0)
			ChangeCurrentState(GAME_OVER);

		if (IM.CheckKeyState(SDLK_p, PRESSED) || IM.CheckKeyState(SDLK_ESCAPE, PRESSED))
			ChangeCurrentState(PAUSE);

		break;

	case PAUSE:

		if (IM.CheckKeyState(SDLK_p, PRESSED) || IM.CheckKeyState(SDLK_ESCAPE, PRESSED) || buttons[0]->GetActivated())
			ChangeCurrentState(GAME);
		else if (buttons[1]->GetActivated())
		{
			nextScene = MAIN; 
			isFinished = true; 
		}

		break;
	case FINISH_STATE:

		if (!player->IsPlayerPaused())
			ChangeCurrentState(GAME);
		
		break;
	case HIT:

		if (!player->PlayerHitted() && LIVES_GAME.GetLives() != 0)
			ChangeCurrentState(GAME);

		break;

	case GAME_OVER:

		break;
	default:
		break;
	}
}

void Gameplay::ChangeCurrentState(StatesGameplay nextState)
{
	if (currentState == nextState)
		return; 

	switch (nextState)
	{
	case GAME:

		if (currentState == PAUSE)
		{
			ui[0]->GetRenderer()->NewText("  ");
		}
		if (currentState == FINISH_STATE)
		{
			if (currentKeyLevel == 2)
				currentKeyLevel = 0;
			else
				currentKeyLevel++;

			remainingWaves = levelLoader.LoadLevel(currentKeyLevel);
			ui[1]->GetRenderer()->NewText("  ");
		}
		break;

	case PAUSE:
		ui[0]->GetRenderer()->NewText("PAUSED");
		break;

	case FINISH_STATE:
		ui[1]->GetRenderer()->NewText("PRESS SPACE TO CONTINUE");
		break;

	case HIT:

		break;

	case GAME_OVER:
		ResetAll(); 
		break;

	default:
		break;
	}
	currentState = nextState;
}

void Gameplay::GameState(float dt)
{
	UpdateIslands(dt);

	ui[2]->GetRenderer()->NewText("R: " + std::to_string(player->GetAvaliableRolls()));

	//Control waves
	for (int i = remainingWaves.size() - 1; i >= 0; i--)
	{
		if (remainingWaves[i]->WaveDone())
		{
			remainingWaves.erase(remainingWaves.begin() + i);
			continue;
		}
		remainingWaves[i]->Update(dt);
	}
	if (remainingWaves.size() < 1)
	{
		ship->Finished();
	}
}
void Gameplay::UpdateIslands(float dt)
{
	currentTimeToSpawnIsland += dt;
	if (currentTimeToSpawnIsland >= timeToSpawnIsland)
	{
		currentTimeToSpawnIsland = 0;
		SpawnIsland();
	}
}

void Gameplay::GamePaused(float dt)
{
	for (Button* button : buttons)
	{
		for (Button* other : buttons)
			button->OnCollisionEnter(other); 
	}
}

void Gameplay::FinishState(float dt)
{
}

void Gameplay::HitState(float dt)
{
	// Elimina todos los enemigos, powerups, bullets...
	for (int i = objects.size() - 1; i >= 0; i--)
	{
		if (dynamic_cast<SeaBackground*>(objects[i]) ||
			dynamic_cast<ShipBackGround*>(objects[i]) ||
			dynamic_cast<Player*>(objects[i]))
			continue;

		delete objects[i];
		objects.erase(objects.begin() + i);
	}

	//No spawnees lo que tenias que spawnear
	SPAWNER.ClearSpawnQueue();
}

void Gameplay::ResetAll()
{
	for (int i = remainingWaves.size() - 1; i >= 0; i--)
		remainingWaves.erase(remainingWaves.begin() + i);

	AUDIO.ClearClips();
	// SCORE.Reset();
	SPAWNER.ClearSpawnQueue();

	// Elimina todos los enemigos, powerups, bullets...
	for (int i = objects.size() - 1; i >= 0; i--)
	{
		if (dynamic_cast<SeaBackground*>(objects[i]) ||
			dynamic_cast<ShipBackGround*>(objects[i]) ||
			dynamic_cast<Player*>(objects[i]))
			continue;

		delete objects[i];
		objects.erase(objects.begin() + i);
	}

	levelLoader.clearLevels();
	levelLoader.SetLevels(levelLoader.ReadAllLevels(player));

	currentKeyLevel = 0;
	remainingWaves = levelLoader.LoadLevel(currentKeyLevel);
	SCORE.planesPerStage = GetPlanesPerStage();

	ship->Reset();
	player->Reset();
	ui[0]->GetRenderer()->NewText(" ");
}

int Gameplay::GetPlanesPerStage() const
{
	int planesPerStage = 0;
	int size = remainingWaves.size();

	for (int i = 0; i < size; i++)
	{
		planesPerStage += remainingWaves[i]->GetWaveSize();
	}

	return planesPerStage;
}
