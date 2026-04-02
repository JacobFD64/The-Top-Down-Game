#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Map.h"
#include "nlohmann/json.hpp"
#include <stdexcept>

class JsonLoader
{
public:
	static nlohmann::json loadJson (const std::string& path);
	static Map LoadMapFromJson(std::string path);
	static std::vector<int> LoadCoinPositionsFromJson(std::string path);

private:


};