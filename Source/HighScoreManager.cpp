#include "HighScoreManager.h"


void HighScoreManager::InitializeHighScores()
{
	for (int i = 0; i < 10; i++)
	{
		UserScore user(0000, "---");
		highScores.push_back(user);
	}
	SCOREM.SaveScores(scoreFile);
}

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

void HighScoreManager::AddScores(UserScore uScore)
{
	int count = 0;

	std::vector<UserScore>::iterator it = highScores.begin();

	for (it; it != highScores.end() - 1; it++)
	{
		if (uScore >= *it)
		{
			highScores.insert(highScores.begin() + count, uScore);
			break;
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
