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
		std::string printScore;
		for (int i = std::to_string(score).length(); i < 6; i++)
			printScore.append("0");
		printScore.append(std::to_string(score));

		scoreUI = new TextObject(printScore, 15, { 255, 255, 0 },
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

	inline void AddScore(int amount) 
	{ 
		// SUM SCORE
		score += amount;

		// UPDATE TEXT SCORE
 		std::string printScore; 
		for (int i = std::to_string(score).length(); i < 6; i++)
			printScore.append("0");
 		printScore.append(std::to_string(score));

		// DRAW
		scoreUI->GetRenderer()->NewText(printScore);
	}
	inline TextObject* GetScoreUI() const { return scoreUI; }
	inline void Reset() 
	{
		score = 0; 
		AddScore(0); 
	}
};