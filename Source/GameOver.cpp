#include "GameOver.h"

GameOver::GameOver()
{
	isFinished = false; 
	nextScene = MAIN; 
	writtingName = true; 
	inputText = " ";
}

void GameOver::OnEnter()
{
	ChangeWritting(true); 
	RENDERER.SetWindowsColor(0, 0, 0);
}

void GameOver::Update(float dt)
{
	if (writtingName)
	{
		Writting(); 
	}
	else
	{
		Scene::Update(dt);
		if (dynamic_cast<Button*>(objects[0])->GetActivated()) // restart
		{
			nextScene = GAMEPLAY;
			isFinished = true;
		}
		else if (dynamic_cast<Button*>(objects[1])->GetActivated()) // back to main
		{
			nextScene = MAIN;
			isFinished = true;
		}
	}
}

void GameOver::WriteInScreen()
{
	if (IM.CheckKeyState(SDLK_BACKSPACE, PRESSED) && inputText.size() > 0)
	{
		inputText.pop_back();
		return; 
	}

	if (inputText.length() >= 7)
	{
		ui[1]->GetRenderer()->NewText("max characters");
		return;
	}
	else
		ui[1]->GetRenderer()->NewText("Space to continue");

	if (IM.CheckKeyState(SDLK_q, RELEASED))
	{
		inputText += "Q"; 
	}
	else if (IM.CheckKeyState(SDLK_w, RELEASED))
	{
		inputText += "W";
	}
	else if (IM.CheckKeyState(SDLK_e, RELEASED))
	{
		inputText += "E";
	}
	else if (IM.CheckKeyState(SDLK_r, RELEASED))
	{
		inputText += "R";
	}
	else if (IM.CheckKeyState(SDLK_t, RELEASED))
	{
		inputText += "T";
	}
	else if (IM.CheckKeyState(SDLK_y, RELEASED))
	{
		inputText += "Y";
	}
	else if (IM.CheckKeyState(SDLK_u, RELEASED))
	{
		inputText += "U";
	}
	else if (IM.CheckKeyState(SDLK_i, RELEASED))
	{
		inputText += "I";
	}
	else if (IM.CheckKeyState(SDLK_o, RELEASED))
	{
		inputText += "O";
	}
	else if (IM.CheckKeyState(SDLK_p, RELEASED))
	{
		inputText += "P";
	}
	else if (IM.CheckKeyState(SDLK_a, RELEASED))
	{
		inputText += "A";
	}
	else if (IM.CheckKeyState(SDLK_s, RELEASED))
	{
		inputText += "S";
	}
	else if (IM.CheckKeyState(SDLK_d, RELEASED))
	{
		inputText += "D";
	}
	else if (IM.CheckKeyState(SDLK_f, RELEASED))
	{
		inputText += "F";
	}
	else if (IM.CheckKeyState(SDLK_g, RELEASED))
	{
		inputText += "G";
	}
	else if (IM.CheckKeyState(SDLK_h, RELEASED))
	{
		inputText += "H";
	}
	else if (IM.CheckKeyState(SDLK_j, RELEASED))
	{
		inputText += "J";
	}
	else if (IM.CheckKeyState(SDLK_k, RELEASED))
	{
		inputText += "K";
	}
	else if (IM.CheckKeyState(SDLK_l, RELEASED))
	{
		inputText += "L";
	}
	else if (IM.CheckKeyState(SDLK_z, RELEASED))
	{
		inputText += "Z";
	}
	else if (IM.CheckKeyState(SDLK_x, RELEASED))
	{
		inputText += "X";
	}
	else if (IM.CheckKeyState(SDLK_c, RELEASED))
	{
		inputText += "C";
	}
	else if (IM.CheckKeyState(SDLK_v, RELEASED))
	{
		inputText += "V";
	}
	else if (IM.CheckKeyState(SDLK_b, RELEASED))
	{
		inputText += "B";
	}
	else if (IM.CheckKeyState(SDLK_n, RELEASED))
	{
		inputText += "N";
	}
	else if (IM.CheckKeyState(SDLK_m, RELEASED))
	{
		inputText += "M";
	}
}

void GameOver::Writting()
{
	WriteInScreen();

	if (inputText != "")
	{
		ui[0]->GetRenderer()->NewText(inputText);

		if (IM.CheckKeyState(SDLK_SPACE, PRESSED) || IM.CheckKeyState(SDLK_RETURN, PRESSED))
			ChangeWritting(false); 
	}
	else
	{
		ui[0]->GetRenderer()->NewText(".......");
		ui[1]->GetRenderer()->NewText(" ");
	}
}

void GameOver::ChangeWritting(bool write)
{
	if (write) 
	{
		inputText = ""; 

		// Clear screen
		objects.clear();
		ui.clear();

		// New UI 
		// 0 -> NamePlayer!!! Don't move
		ui.push_back(new TextObject(" ", 20, { 255, 255, 255 },
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 150), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));
		// 1 -> Space!!! Don't move
		ui.push_back(new TextObject("Space to continue", 12, { 200, 200, 200 },
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 200), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));

		ui.push_back(new TextObject("Write your name for ranking: ", 12, { 200, 200, 200 },
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 100), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));
	}
	else
	{
		// Add score and name to HighScore
		UserScore uScore(SCORE.GetScore(), inputText);
		HIGHSCOREM.AddScores(uScore);

		// Clear screen
		objects.clear(); 
		ui.clear(); 

		// New UI
		int textSize = 15;
		SDL_Color textColor = { 255, 255, 255 }; 
		ui.push_back(new TextObject(std::to_string(LIVES_GAME.GetLives()) + "UP", textSize, textColor,
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.15, 50), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));

		std::string printScore;
		for (int i = std::to_string(uScore.score).length(); i < 6; i++)
			printScore.append("0");
		printScore.append(std::to_string(uScore.score));

		ui.push_back(new TextObject(printScore, textSize, textColor,
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.15, 75), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));

		ui.push_back(new TextObject("HI-SCORE", textSize, textColor,
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 50), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));
		ui.push_back(new TextObject("999999...", textSize, textColor,
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 75), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));

		ui.push_back(new TextObject("SHOOTING DOWN", textSize, textColor,
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.15, 125), 0, Vector2(1, 1), Vector2(30, 30), false),
			"Resources/PixelPowerline-11Mg.ttf"));
		
		ui.push_back(new TextObject("PERCENTATGE", textSize, textColor,
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.15, 150), 0, Vector2(1, 1), Vector2(30, 30), false),
			"Resources/PixelPowerline-11Mg.ttf"));

		ui.push_back(new TextObject(inputText, textSize, { 255, 255, 0},
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 225), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));

		ui.push_back(new TextObject("GAME OVER", textSize, textColor,
			new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 275), 0, Vector2(1, 1), Vector2(30, 30), true),
			"Resources/PixelPowerline-11Mg.ttf"));

		// New objects
		objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 370), "RESTART"));
		objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 450), "BACK TO MAIN"));
	}
	writtingName = write; 
}
