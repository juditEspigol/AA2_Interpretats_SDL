#include "LevelLoader.h"

std::vector<Wave> LevelLoader::LoadLevel(int key)
{
	for (std::pair<int, std::vector<Wave>> myPair : levels)
	{
		if (key == myPair.first)
			return myPair.second;
	}
}

std::unordered_map<int, std::vector<Wave>> LevelLoader::ReadAllLevels(Player* _player)
{
	std::unordered_map<int, std::vector<Wave>> mapLevels;

	int key = 0;

	mapLevels.emplace(key, ReadOneLevel("Resources/Levels/stage_0.xml", _player));
	key++;

	mapLevels.emplace(key, ReadOneLevel("Resources/Levels/stage_1.xml", _player));
	key++;

	mapLevels.emplace(key, ReadOneLevel("Resources/Levels/stage_2.xml", _player));
	key++;

	/*mapLevels.emplace(key, ReadOneLevel("Resources/Levels/stage_3.xml", _player));
	key++;

	mapLevels.emplace(key, ReadOneLevel("Resources/Levels/stage_4.xml", _player));
	key++;

	mapLevels.emplace(key, ReadOneLevel("Resources/Levels/stage_5.xml", _player));*/

	return mapLevels;
}

std::vector<Wave> LevelLoader::ReadOneLevel(std::string _path, Player* _player)
{
	std::vector<Wave> planesToSpawn;

	rapidxml::xml_document<> document;
	std::ifstream myFile;
	myFile.open(_path);

	if (!myFile.is_open())
	{
		std::cout << "The file can't be opened";
	}

	std::stringstream buffer;
	buffer << myFile.rdbuf();
	myFile.close();

	std::string content(buffer.str());
	document.parse<0>(&content[0]);
	rapidxml::xml_node<>* root = document.first_node();

	rapidxml::xml_attribute<>* waveAtribute;

	float spawnTime;
	WaveType waveType;
	Pattern pattern;

	for (rapidxml::xml_node<>* waveNode = root->first_node("wave"); waveNode; waveNode = waveNode->next_sibling())
	{
		spawnTime = std::stof(waveNode->first_node("spawnTime")->value());
		waveType = (WaveType)std::stoi(waveNode->first_node("type")->value());

		if (waveNode->first_node("type")->first_attribute("pattern") != NULL)
		{
			waveAtribute = waveNode->first_node("type")->first_attribute("pattern");
			pattern = (Pattern)std::stoi(waveAtribute->value());
		}

		Wave wave(spawnTime, waveType, pattern, _player);

		planesToSpawn.push_back(wave);
	}

	return planesToSpawn;
}
