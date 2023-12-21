#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Wave.h"

#include "rapidXML/rapidxml.hpp"
#include "rapidXML/rapidxml_iterators.hpp"
#include "rapidXML/rapidxml_print.hpp"
#include "rapidXML/rapidxml_utils.hpp"

#define LEVELLOADER LevelLoader::Instance()

class LevelLoader
{

	LevelLoader() = default;
	LevelLoader(const LevelLoader&) = delete;
	LevelLoader& operator =(const LevelLoader&) = delete;

public:

	inline static LevelLoader& Instance()
	{
		static LevelLoader levelLoader;
		return levelLoader;
	}

	std::vector<Wave> LoadLevel(std::string _path);
};