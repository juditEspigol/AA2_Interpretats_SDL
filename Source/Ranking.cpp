#include "Ranking.h"

Ranking::Ranking()
{
	isFinished = false;
	nextScene = MAIN;

	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.50, 450), "BACK", Vector2(100, 40)));


	ui.push_back(new TextObject("RANKING:", 25, {255, 255, 255},
		new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 50), 0, Vector2(1, 1), Vector2(30, 30), true),
		"Resources/PixelPowerline-11Mg.ttf"));


	HIGHSCOREM.InitializeHighScores(); 
	Vector2 position = Vector2(RENDERER.GetSizeWindow().x * 0.55, RENDERER.GetSizeWindow().y * 0.17);
	int i = 0; 
	for (int score : HIGHSCOREM.GetScores())
	{
		if (i < 3)
		{
			//SCORE 
			ui.push_back(new TextObject(std::to_string(score), 20, { 255, 255, 0 },
				new Transform(position, 0, Vector2(1, 1), Vector2(30, 30), false),
				"Resources/PixelPowerline-11Mg.ttf"));
			// NAME
			if (score != 0)
			{
				if(i == 0)
					ui.push_back(new TextObject("RADEV", 20, { 255, 255, 0 },
						new Transform(position - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
						"Resources/PixelPowerline-11Mg.ttf"));
				else if(i == 1)
					ui.push_back(new TextObject("JORDI", 20, { 255, 255, 0 },
						new Transform(position - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
						"Resources/PixelPowerline-11Mg.ttf"));
				else if (i == 2)
					ui.push_back(new TextObject("EDU", 20, { 255, 255, 0 },
						new Transform(position - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
						"Resources/PixelPowerline-11Mg.ttf"));
			}
			else
			{
				ui.push_back(new TextObject("---", 20, { 255, 255, 0 },
					new Transform(position - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
					"Resources/PixelPowerline-11Mg.ttf"));
			}
		}
		else
		{
			// SCORE
			ui.push_back(new TextObject(std::to_string(score), 20, { 200, 200, 200 },
				new Transform(position, 0, Vector2(1, 1), Vector2(30, 30), false),
				"Resources/PixelPowerline-11Mg.ttf"));
			// NAME
			if (score != 0)
			{
				ui.push_back(new TextObject("ALEXIÑO", 20, { 200, 200, 200 },
					new Transform(position - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
					"Resources/PixelPowerline-11Mg.ttf"));
			}
			else
			{
				ui.push_back(new TextObject("---", 20, { 200, 200, 200 },
					new Transform(position - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
					"Resources/PixelPowerline-11Mg.ttf"));
			}
		}
		position = position + Vector2(0, 30); 
		i++; 
	}
}

void Ranking::OnEnter()
{
}

void Ranking::Update(float dt)
{
	Scene::Update(dt);

	if (dynamic_cast<Button*>(objects[0])->GetActivated()) // back
		isFinished = true;
}