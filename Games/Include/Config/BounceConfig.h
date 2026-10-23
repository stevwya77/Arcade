#pragma once

#include "Scene/Scene.h"
#include <string>
#include <string_view>

namespace Bounce 
{
    /* Paddle Config */
    const int PADDLE_LIVES = 10;
    const sf::Vector2f PADDLE_SIZE(120, 20);
    const float PADDLE_SPEED = 750;
    const sf::Color PADDLE_COLOR(sf::Color::Green);

    /* Ball Config */
    const float BALL_RADIUS = 10;
    const float BALL_SPEED = 250;
    const sf::Color BALL_COLOR(sf::Color::Cyan);
    const float BALL_SPAWN_COOLDOWN_DURATION = 2;

    /* Stats Config */
    const sf::Color STATS_SCORE_TEXT_COLOR(sf::Color::Cyan);
    const std::string_view STATS_HIGH_SCORE_KEY = "Bounce:High Score";
    const sf::Color STATS_HIGH_SCORE_TEXT_COLOR(sf::Color::Yellow);
    const sf::Color STATS_LIVES_TEXT_COLOR(sf::Color::Red);

    /* Background */
    const std::string BACKGROUND_TEXTURE_FILENAME = "BounceBg.png";

    /* Sound FX */
    const std::string BOUNCE_SOUND_FILENAME = "Bounce.wav";
    const float BOUNCE_SOUND_VOLUME = 1;

    /* Music */
    const std::string MUSIC_FILENAME = "Music.wav";
    const float MUSIC_VOLUME = 50;
    const float MUSIC_PITCH = 1;
}