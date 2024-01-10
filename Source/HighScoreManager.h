#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "UserScore.h"

const std::string scoreFile = "HighScore.dat";
#define HIGHSCOREM HighScoreManager::Instance()

class HighScoreManager
{
private:

	std::vector<UserScore> highScores;

	int numMaxOfHighScores;


	HighScoreManager() = default;

	HighScoreManager(const HighScoreManager&) = delete;
	HighScoreManager& operator =(const HighScoreManager&) = delete;

public:

	inline static HighScoreManager& Instance()
	{ 
		static HighScoreManager scoreM;
		return scoreM;
	}

	void InitializeHighScores();
	void CreateNewHighScore();


	bool CheckIfThereIsHighScore();

	inline bool CompareFunc(UserScore& leftNumber, UserScore& RightNumber) { return leftNumber.score > RightNumber.score; };

	void SaveScores(std::string path);
	void LoadScores(std::string path);
	void AddScores(UserScore score);
	std::vector<UserScore> GetScores();

};
