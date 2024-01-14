#pragma once
#include "Scene.h"

// DEPENDENCIES
#include "ScoreManager.h"
#include "HighScoreManager.h"
#include "Button.h"
#include "UserScore.h"
#include "LivesManager.h"

class GameOver : public Scene
{
private:
	bool writtingName;
	std::string inputText;
public:
	GameOver(); 

	void OnEnter() override; 

	void Update(float dt) override;

	void WriteInScreen(); 
	void Writting(); 
	void ChangeWritting(bool write); 
};