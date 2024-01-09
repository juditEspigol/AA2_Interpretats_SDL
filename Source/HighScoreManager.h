#pragma once
#include "UserScore.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>


const std::string scoreFile = "HighScore.dat";
#define SCOREM HighScoreManager::Instance()

class HighScoreManager
{
private:

	std::vector<UserScore> highScores;

	int numMaxOfHighScores;


	HighScoreManager()
		: numMaxOfHighScores(10) {
		InitializeHighScores();
	};

	HighScoreManager(const HighScoreManager&) = delete;
	HighScoreManager& operator =(const HighScoreManager&) = delete;

public:

	inline static HighScoreManager& Instance()
	{
		static HighScoreManager scoreM;
		return scoreM;
	}

	void InitializeHighScores();

	void SaveScores(std::string path);
	void LoadScores(std::string path);
	void AddScores(UserScore uScore);
	std::vector<UserScore> GetScores();
};
