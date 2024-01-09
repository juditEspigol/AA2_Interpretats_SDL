#include "HighScoreManager.h"


void HighScoreManager::InitializeHighScores()
{
	numMaxOfHighScores = 10;

	if (CheckIfThereIsHighScore())
		LoadScores(scoreFile);
	else
		InitializeHighScores();
}

void HighScoreManager::CreateNewHighScore()
{
	for (int i = 0; i < 10; i++)
	{
		UserScore user(0000, "---");
		highScores.push_back(user);
	}
	SCOREM.SaveScores(scoreFile);
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

void HighScoreManager::AddScores(UserScore uScore)
{
	bubbleSort(highScores);
	highScores.push_back(uScore);


	if (highScores.size() > 10)
		highScores.pop_back();
}

std::vector<UserScore> HighScoreManager::GetScores()
{
    return highScores;
}

void HighScoreManager::bubbleSort(std::vector<UserScore>& vector) 
{
	int n = vector.size();
	bool swapped;
	for (int i = 0; i < n - 1; i++) {
		swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (vector[j] >= vector[j + 1]) {
				std::swap(vector[j], vector[j + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
	}
}
