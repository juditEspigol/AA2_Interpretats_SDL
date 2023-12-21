#include "LevelLoader.h"

std::vector<Wave> LevelLoader::LoadLevel(std::string _path)
{
    std::vector<Wave> planesToSpawn;

	rapidxml::xml_document<> document;
	std::ifstream myFile;
	myFile.open("../stage_0.xml");

	if (!myFile.is_open())
	{
		std::cout << "The file can't be opened";
		return;
	}

	std::stringstream buffer;
	buffer << myFile.rdbuf();
	myFile.close();

	std::string content(buffer.str());
	document.parse<0>(&content[0]);
	rapidxml::xml_node<>* root = document.first_node();

	for (rapidxml::xml_node<>* WaveNode = root->first_node("wave"); WaveNode; WaveNode = WaveNode->next_sibling())
	{
		rapidxml::xml_node<>* gameObjectNode;
		//Wave(float _startTime, WaveType _waveType, Player * _player);



		for (gameObjectNode = gameObjectNode->first_node(); gameObjectNode; gameObjectNode = gameObjectNode->next_sibling())
		{
			
			
		}
	}

    return planesToSpawn;
}
