#pragma once
#include <string>

struct UserScore
{
	int score;
	std::string name;

	UserScore() = default;

	UserScore(int score, std::string name)
		: score(score), name(name) {}

	void WriteUserScoreVector(std::ofstream file, std::vector<UserScore>& vector)
	{
		int size = vector.size();
		file.write(reinterpret_cast<char*>(&size), sizeof(int));

		for (int i = 0; i < size; i++)
		{
			file.write(reinterpret_cast<char*>(&vector[i].score), sizeof(int));

			size_t wordSize = vector[i].name.length();
			file.write(reinterpret_cast<char*>(&vector[i].name), sizeof(wordSize));

			//Write the actual string
			file.write(vector[i].name.c_str(), size);
		}
	}

	void ReadUserScoreVector(std::ifstream file, std::vector<UserScore>& vector)
	{

	}

	inline bool operator>(const UserScore& uScore) const
	{
		return score > uScore.score;
	}
};