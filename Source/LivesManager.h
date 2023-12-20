#pragma once
#include "TextObject.h"

#define LIVES_GAME LivesManager::Instance()

class LivesManager
{
private:
	int lives;
	TextObject* livesUI;

	LivesManager()
		: lives(3)
	{
		std::string priintLives = "HP: ";
		for (int i = lives; i > 0; i--)
			priintLives.append("O");

		livesUI = new TextObject(priintLives, 15, { 0, 255, 0 },
			new Transform(Vector2(10, RENDERER.GetSizeWindow().y - 30), 0, Vector2(1, 1), Vector2(15, 15), false),
			"Resources/PixelPowerline-11Mg.ttf");
	};
	LivesManager(const LivesManager&) = delete;
	LivesManager& operator =(const LivesManager&) = delete;

public:
	inline static LivesManager& Instance()
	{
		static LivesManager manager;
		return manager;
	}

	inline void SubstractLives(int amount)
	{
		// SUM SCORE
		lives -= amount;

		// UPDATE TEXT SCORE
		std::string priintLives = "HP: ";
		for (int i = lives; i > 0; i--)
			priintLives.append("O");

		// DRAW
		livesUI->GetRenderer()->NewText(priintLives);
	}
	inline TextObject* GetLivesUI() const { return livesUI; }
	inline int GetLives() const { return lives; }
};