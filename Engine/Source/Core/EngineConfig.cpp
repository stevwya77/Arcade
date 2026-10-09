#include "Core/EngineConfig.h"
#include "SFML/System/Time.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <cassert>

EngineConfig::EngineConfig()
{
    std::ifstream file("Content/Config.json");
    assert(file);

    nlohmann::json json = nlohmann::json::parse(file);
    windowTitle = json["windowTitle"];
    windowSize = {json["windowSize"][0], json["windowSize"][1]};
    disableSFMLLogs = json["disableSFMLLogs"];
    maximumDeltaTime = sf::seconds(json["maximumDeltaTime"]);
}