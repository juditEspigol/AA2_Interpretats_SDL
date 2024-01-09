#include "Ranking.h"
#include "UserScore.h"

Ranking::Ranking()
{
	UserScore user(720, "ABC");
	UserScore user2(502, "ZBC");

	SCOREM.AddScores(user);
	SCOREM.AddScores(user2);
	SCOREM.GetScores();
}
