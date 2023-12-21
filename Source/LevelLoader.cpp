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

	for (rapidxml::xml_node<>* waveNode = root->first_node("wave"); waveNode; waveNode = waveNode->next_sibling())
	{
		float spawnTime = std::stof(waveNode->first_node("spawnTime")->value());
		WaveType waveType = (WaveType)std::stoi(waveNode->first_node("type")->value());
		
		Wave wave(spawnTime, waveType, _player);


		planesToSpawn.push_back(wave);
	}

    return planesToSpawn;
}
