#pragma once
#include "Core/EngineVisitor.h"
#include <SFML/Graphics.hpp>

class Engine
{
private:
    friend EngineVisitor;

    sf::RenderWindow window_;
    
    void EventWindowClose();
    void EventWindowResized(sf::Vector2u size);
    void EventWindowFocusLost();
    void EventWindowFocusGained();

public:
    Engine();

    bool IsRunning() const;

    void ProcessEvents();
    void Update();
    void Render();
};