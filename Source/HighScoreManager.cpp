#include "HighScoreManager.h"

void HighScoreManager::InitializeHighScores()
{
	numMaxOfHighScores = 9;

	if (CheckIfThereIsHighScore())
		LoadScores(scoreFile);
	else
		CreateNewHighScore();
}

void HighScoreManager::CreateNewHighScore()
{
	for (int i = 0; i < numMaxOfHighScores; i++)
	{
		UserScore uScore(000000, "---");
		highScores.push_back(uScore);
	}
	HIGHSCOREM.SaveScores(scoreFile);
}

bool HighScoreManager::CheckIfThereIsHighScore()
{
	std::ifstream myFileIn(scoreFile, std::ios::in | std::ios::binary);

	return myFileIn.is_open();           
}

void HighScoreManager::SaveScores(std::string path)
{
	std::ofstream myFileOut(path, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!myFileOut.is_open())
	{
		std::cout << "The file can't be opened";
	}

	WriteUserScore(myFileOut);

	myFileOut.close();
}

void HighScoreManager::WriteUserScore(std::ofstream& file)
{
	int size = highScores.size();
	file.write(reinterpret_cast<char*>(&size), sizeof(int));

	for (int i = 0; i < size; i++)
	{
		file.write(reinterpret_cast<char*>(&highScores[i].score), sizeof(int));

		size_t wordSize = highScores[i].name.size();
		file.write(reinterpret_cast<char*>(&wordSize), sizeof(wordSize));

		//Write the actual string
		file.write(highScores[i].name.c_str(), wordSize);
	}
}

void HighScoreManager::LoadScores(std::string path)
{
	numMaxOfHighScores = 9;

	std::ifstream myFileIn(path, std::ios::in | std::ios::binary);

	if (!myFileIn.is_open())
	{
		std::cout << "The file can't be opened";
	}

	ReadUserScore(myFileIn);

	myFileIn.close();
}

void HighScoreManager::ReadUserScore(std::ifstream& file)
{
	int size = 0;
	file.read(reinterpret_cast<char*>(&size), sizeof(int));

	highScores.resize(size);

	for (int i = 0; i < size; i++)
	{
		file.read(reinterpret_cast<char*>(&highScores[i].score), sizeof(int));

		size_t stringSize = 0;
		file.read(reinterpret_cast<char*>(&stringSize), sizeof(stringSize));

		char* ptr = new char[stringSize + 1];
		file.read(ptr, stringSize);

		ptr[stringSize] = '\0';
		highScores[i].name = ptr;

		delete[] ptr;
	}
}

void HighScoreManager::AddScores(UserScore score)
{
	std::vector<UserScore> vectorCopy = highScores;

	vectorCopy.push_back(score);

	std::sort(vectorCopy.begin(), vectorCopy.end(), std::greater<UserScore>());

	if (vectorCopy.size() > numMaxOfHighScores)
		vectorCopy.pop_back();
	highScores = vectorCopy;

	SaveScores(scoreFile);
}

std::vector<UserScore> HighScoreManager::GetScores()
{
    return highScores;
}
