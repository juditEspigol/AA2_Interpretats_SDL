#pragma once
#include "UserScore.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>


const std::string scoreFile = "HighScore.dat";

class HighScoreManager
{
private:

	std::vector<UserScore> highScores;

	int numMaxOfHighScores;


	HighScoreManager()
		: numMaxOfHighScores(10) {};

	HighScoreManager(const HighScoreManager&) = delete;
	HighScoreManager& operator =(const HighScoreManager&) = delete;

public:

	inline static HighScoreManager& Instance()
	{
		static HighScoreManager scoreM;
		return scoreM;
	}

	void SaveScores(std::string path);
	void LoadScores(std::string path);
	void AddScores(int value, std::string name);
	std::vector<UserScore> GetScores();
};
