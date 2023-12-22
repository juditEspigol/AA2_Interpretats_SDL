#include "LevelLoader.h"

std::vector<Wave> LevelLoader::LoadLevel(std::string _path, Player* _player)
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
		waveAtribute = waveNode->first_node("type")->first_attribute("pattern");
		pattern = (Pattern)std::stoi(waveAtribute->value());

		Wave wave(spawnTime, waveType, pattern, _player);

		planesToSpawn.push_back(wave);
	}

    return planesToSpawn;
}
