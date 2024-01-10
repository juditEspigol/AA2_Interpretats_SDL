#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>

const std::string scoreFile = "HighScore.dat";
#define HIGHSCOREM HighScoreManager::Instance()

class HighScoreManager
{
private:

	std::vector<int> highScores;

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

	inline bool CompareFunc(int& leftNumber, int& RightNumber) { return leftNumber > RightNumber; };

	void SaveScores(std::string path);
	void LoadScores(std::string path);
	void AddScores(int score);
	std::vector<int> GetScores();

};
