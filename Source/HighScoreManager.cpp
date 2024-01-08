#include "HighScoreManager.h"


void HighScoreManager::SaveScores(std::string path)
{
	std::ofstream myFileOut(path, std::ios::out | std::ios::binary | std::ios::trunc);

	assert(!myFileOut.is_open());

	int size = highscores.size();
	myFileOut.write(reinterpret_cast<char*>(&size), sizeof(int));
	myFileOut.write(reinterpret_cast<char*>(highscores.data()), sizeof(UserScore) * size);

	myFileOut.close();
}

void HighScoreManager::LoadScores(std::string path)
{
	std::ifstream myFileIn(path, std::ios::in | std::ios::binary);

	assert(!myFileIn.is_open());

	int inSize = 0;
	myFileIn.read(reinterpret_cast<char*>(&inSize), sizeof(int));

	highscores.resize(inSize);

	myFileIn.read(reinterpret_cast<char*>(highscores.data()), sizeof(UserScore) * inSize);

	myFileIn.close();
}

void HighScoreManager::AddScores(int value, std::string name)
{
	UserScore uScore(value, name);

	highscores.push_back(uScore);
}

std::vector<UserScore> HighScoreManager::GetScores()
{
    return highscores;
}
