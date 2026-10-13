#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <string>

struct EngineConfig
{
    std::string windowTitle;
    sf::Vector2f windowSize;
    bool disableSFMLLogs;
    sf::Time maximumDeltaTime;
    float globalVolume;

    EngineConfig();
};

inline const EngineConfig gConfig;