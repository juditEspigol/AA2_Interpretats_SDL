#include "Ranking.h"

Ranking::Ranking()
{
	isFinished = false;
	nextScene = MAIN;

	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.50, 460), "BACK", Vector2(100, 40)));
}

void Ranking::OnEnter()
{
	RENDERER.SetWindowsColor(0, 0, 0);
	ui.clear();
	ReadScore();
}

void Ranking::Update(float dt)
{
	Scene::Update(dt);

	if (dynamic_cast<Button*>(objects[0])->GetActivated()) // back
		isFinished = true;
}

void Ranking::ReadScore()
{
	ui.push_back(new TextObject("RANKING:", 25, { 255, 255, 255 },
		new Transform(Vector2(RENDERER.GetSizeWindow().x * 0.5, 50), 0, Vector2(1, 1), Vector2(30, 30), true),
		"Resources/PixelPowerline-11Mg.ttf"));

	Vector2 position = Vector2(RENDERER.GetSizeWindow().x * 0.55, RENDERER.GetSizeWindow().y * 0.17);

	EasterEgg(position);

	int i = 0;
	for (UserScore score : HIGHSCOREM.GetScores())
	{
		position = position + Vector2(0, 30);
		if (i < 2)
		{
			//SCORE 
			ui.push_back(new TextObject(std::to_string(score.score), 20, { 255, 255, 0 },
				new Transform(position, 0, Vector2(1, 1), Vector2(30, 30), false),
				"Resources/PixelPowerline-11Mg.ttf"));

			// NAME
				ui.push_back(new TextObject(score.name, 20, { 255, 255, 0 },
					new Transform(position - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
					"Resources/PixelPowerline-11Mg.ttf"));
		}
		else
		{
			// SCORE
			ui.push_back(new TextObject(std::to_string(score.score), 20, { 200, 200, 200 },
				new Transform(position, 0, Vector2(1, 1), Vector2(30, 30), false),
				"Resources/PixelPowerline-11Mg.ttf"));
			// NAME
			ui.push_back(new TextObject(score.name, 20, {200, 200, 200},
				new Transform(position - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
				"Resources/PixelPowerline-11Mg.ttf"));
		}
		i++;
	}
}

void Ranking::EasterEgg(Vector2 pos)
{
	ui.push_back(new TextObject("9999", 20, { 255, 255, 0 },
		new Transform(Vector2(-10, pos.y), 0, Vector2(1, 1), Vector2(30, 30), false),
		"Resources/PixelPowerline-11Mg.ttf"));

	ui.push_back(new TextObject("RADEV", 20, { 255, 255, 0 },
		new Transform(pos - Vector2(150, 0), 0, Vector2(1, 1), Vector2(30, 30), false),
		"Resources/PixelPowerline-11Mg.ttf"));

	ui.push_back(new TextObject("9999999999999999999", 20, { 255, 255, 0 },
		new Transform(pos, 0, Vector2(1, 1), Vector2(30, 30), false),
		"Resources/PixelPowerline-11Mg.ttf"));
}
