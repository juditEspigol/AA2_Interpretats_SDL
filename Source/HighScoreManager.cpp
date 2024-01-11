#include "HighScoreManager.h"

void HighScoreManager::InitializeHighScores()
{
	numMaxOfHighScores = 10;

	if (CheckIfThereIsHighScore())
		LoadScores(scoreFile);
	else
		CreateNewHighScore();
}

void HighScoreManager::CreateNewHighScore()
{
	for (int i = 0; i < 10; i++)
	{
		UserScore uScore(000000, "---");
		highScores.push_back(uScore);
	}
	HIGHSCOREM.SaveScores(scoreFile);
}

bool HighScoreManager::CheckIfThereIsHighScore()
{
	std::ifstream myFileIn(scoreFile, std::ios::in | std::ios::binary);

	bool _case;

	if (!myFileIn.is_open())
		_case = false;
	else
		_case = true;

	myFileIn.close();
	return _case;
}

void HighScoreManager::SaveScores(std::string path)
{
	std::ofstream myFileOut(path, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!myFileOut.is_open())
	{
		std::cout << "The file can't be opened";
	}

	int size = highScores.size();
	myFileOut.write(reinterpret_cast<char*>(&size), sizeof(int));
	myFileOut.write(reinterpret_cast<char*>(highScores.data()), sizeof(UserScore) * size);

	myFileOut.close();
}

void HighScoreManager::LoadScores(std::string path)
{
	numMaxOfHighScores = 10;

	std::ifstream myFileIn(path, std::ios::in | std::ios::binary);

	if (!myFileIn.is_open())
	{
		std::cout << "The file can't be opened";
	}

 	int inSize = 0;
	myFileIn.read(reinterpret_cast<char*>(&inSize), sizeof(int));

	highScores.resize(inSize);

	myFileIn.read(reinterpret_cast<char*>(highScores.data()), sizeof(UserScore) * inSize);
	
	myFileIn.close();
}

void HighScoreManager::AddScores(UserScore score)
{
	std::vector<UserScore> vectorCopy = highScores;

	vectorCopy.push_back(score);

	std::sort(vectorCopy.begin(), vectorCopy.end(), std::greater<UserScore>());

	if (vectorCopy.size() > 10)
		vectorCopy.pop_back();
	highScores = vectorCopy;

	SaveScores(scoreFile);
}

std::vector<UserScore> HighScoreManager::GetScores()
{
    return highScores;
}
