#pragma once

#include "OSLayer.hpp"
#include "keybinds.hpp"

#include <string_view>
#include <vector>
#include <fstream>
#include <raylib.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct configOptions
{
	Keybind toggleKeybind {};
	VectorXY<int> options {};
	Color valid {};
	Color invalid {};
	Color shadow {};
	Color text {};
};

class ConfigReader
{
public:
    json data;
    std::ifstream file;

    ConfigReader(std::string_view path = "config/config.json");

    std::vector<int> GetModifiers();

    char GetKey();

    std::pair<int, int> GetOptions();

    std::array<Color, 4> GetColours();

    // void exportDefault();

};