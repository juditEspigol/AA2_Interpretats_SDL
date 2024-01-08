#include "HighScoreManager.h"


void HighScoreManager::SaveScores(std::string path)
{
	std::ofstream myFileOut(path, std::ios::out | std::ios::binary | std::ios::trunc);

	assert(!myFileOut.is_open());

	int size = highScores.size();
	myFileOut.write(reinterpret_cast<char*>(&size), sizeof(int));
	myFileOut.write(reinterpret_cast<char*>(highScores.data()), sizeof(UserScore) * size);

	myFileOut.close();
}

void HighScoreManager::LoadScores(std::string path)
{
	std::ifstream myFileIn(path, std::ios::in | std::ios::binary);

	assert(!myFileIn.is_open());

	int inSize = 0;
	myFileIn.read(reinterpret_cast<char*>(&inSize), sizeof(int));

	highScores.resize(inSize);

	myFileIn.read(reinterpret_cast<char*>(highScores.data()), sizeof(UserScore) * inSize);

	myFileIn.close();
}

void HighScoreManager::AddScores(int value, std::string name)
{
	UserScore uScore(value, name);

	int count = 0;

	for (UserScore userScore : highScores)
	{
		if (uScore >= userScore)
		{
			highScores.insert(highScores.begin() + count, uScore);
			return;
		}
		count++;                                                         
	}

	if (highScores.size() > 10)
		highScores.pop_back();
}

std::vector<UserScore> HighScoreManager::GetScores()
{
    return highScores;
}
