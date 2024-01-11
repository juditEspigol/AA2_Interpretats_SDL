#pragma once
#include <string>

struct UserScore
{
	int score;
	std::string name;

	UserScore() = default;

	UserScore(int score, std::string name)
		: score(score), name(name) {}

	inline bool operator>(const UserScore& uScore) const
	{
		return score > uScore.score;
	}

	std::string GetName() const { return name; }
};