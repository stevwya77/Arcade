#pragma once

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

class CursorManager
{
private:
    friend class Engine;
    sf::RenderWindow& window_;
    sf::CircleShape shape_;
    float speed_;
    bool visible_;
    void Update(float deltaTime);
    void Render() const;

public:
    CursorManager(sf::RenderWindow& window);

    void SetSpeed(float speed);
    float GetSpeed() const;

    void SetVisible(bool visible);
    bool IsVisible() const;

    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetPosition(const sf::View& view) const;
};