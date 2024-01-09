#pragma once
#include "UserScore.h"

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

const std::string scoreFile = "HighScore.dat";
#define SCOREM HighScoreManager::Instance()

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

	void SaveScores(std::string path);
	void LoadScores(std::string path);
	void AddScores(UserScore uScore);
	std::vector<UserScore> GetScores();

	void bubbleSort(std::vector<UserScore>& vector);
};
