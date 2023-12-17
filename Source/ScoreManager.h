#pragma once
#include "TextObject.h"
#define SCORE ScoreManager::Instance()

class ScoreManager
{
private:
	int score; 
	TextObject* scoreUI; 

	ScoreManager()
		: score(0) 
	{
		scoreUI = new TextObject(std::to_string(score), 15, { 255, 255, 0 },
			new Transform(Vector2(10, 30), 0, Vector2(1, 1), Vector2(15, 15), false),
			"Resources/PixelPowerline-11Mg.ttf"); 
	};
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator =(const ScoreManager&) = delete;

public: 
	inline static ScoreManager& Instance()
	{
		static ScoreManager manager;
		return manager;
	}

	inline void AddScore(int amount) { score += amount; }
	inline int GetScore() const { return score; }
	inline TextObject* GetScoreUI() const { return scoreUI; }
};