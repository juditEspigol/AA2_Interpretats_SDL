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
	inline int GetFirstScore() const { return highScores[0].score; }

	void SaveScores(std::string path);
	void WriteUserScore(std::ofstream& file);
	void LoadScores(std::string path);
	void ReadUserScore(std::ifstream& file);
	void AddScores(UserScore score);
	std::vector<UserScore> GetScores();

};
