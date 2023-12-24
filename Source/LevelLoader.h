#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Wave.h"
#include "Player.h"

#include "rapidXML/rapidxml.hpp"
#include "rapidXML/rapidxml_iterators.hpp"
#include "rapidXML/rapidxml_print.hpp"
#include "rapidXML/rapidxml_utils.hpp"

#define LEVELLOADER LevelLoader::Instance()

class LevelLoader
{
	std::unordered_map<int, std::vector<Wave*>> levels;

public:

	LevelLoader() = default;

	LevelLoader(Player* _player) {
		levels = ReadAllLevels(_player);
	};

	std::vector<Wave*> LoadLevel(int key);

	std::unordered_map<int, std::vector<Wave*>> ReadAllLevels(Player* _player);

	std::vector<Wave*>ReadOneLevel(std::string _path, Player* _player);

	void clearLevels();

	inline void SetLevels(std::unordered_map<int, std::vector<Wave*>> _levels) { levels = _levels; }
};