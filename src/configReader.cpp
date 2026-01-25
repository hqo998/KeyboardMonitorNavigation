#include "configReader.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string_view>
#include <raylib.h>
#include <vector>
#include <iostream>

#include <print>

using json = nlohmann::json;



ConfigReader::ConfigReader(std::string_view path)
{
    file.open(path);
    try

    {
        this->data = json::parse(file);
    }
    catch (json::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }
}

std::vector<int> ConfigReader::GetModifiers()
{
    std::string keybind = data["toggleKeybind"]["modifiers"].dump();
    std::println("Modifer Keys: {}", keybind);


    return {};
}

char ConfigReader::GetKey()
{
    std::string keybind = data["toggleKeybind"]["key"].dump();
    std::println("Trigger Key: {}", keybind);
    return keybind.at(0);
}

std::pair<int, int> ConfigReader::GetOptions()
{
    return {};
}

std::array<Color, 4> ConfigReader::GetColours()
{
    return {};
}

// void ConfigReader::exportDefault()
// {
//     configOptions.a =
//     if (file.open())
//     {
//         file << data.dump()
//         file.close()
//     }
// }