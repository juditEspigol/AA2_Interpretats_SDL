#pragma once
#include <string>

struct UserScore
{
	int score;
	std::string name;

	UserScore(int score, std::string name)
		: score(score), name(name) {}

	bool operator>= (UserScore uScore)
	{
		return this->score >= uScore.score;
	}
};