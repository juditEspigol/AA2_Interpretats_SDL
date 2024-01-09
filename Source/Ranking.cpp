#include "Ranking.h"
#include "UserScore.h"

Ranking::Ranking()
{
	UserScore uScore8(509, "ABC");
	UserScore uScore7(508, "ABC");
	UserScore uScore6(507, "ABC");
	UserScore uScore5(506, "ABC");
	UserScore uScore4(505, "ABC");
	UserScore uScore3(504, "ABC");
	UserScore uScore2(503, "ABC");
	UserScore uScore1(502, "ABC");
	UserScore uScore(501, "ABC");

	SCOREM.AddScores(uScore);
	SCOREM.AddScores(uScore1);
	SCOREM.AddScores(uScore6);
	SCOREM.AddScores(uScore3);
	SCOREM.AddScores(uScore8);
	SCOREM.AddScores(uScore4);
	SCOREM.AddScores(uScore7);
	SCOREM.AddScores(uScore5);
	SCOREM.AddScores(uScore2);

	SCOREM.GetScores();
}
