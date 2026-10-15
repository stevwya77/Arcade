#pragma once

#include <SFML/Graphics.hpp>
#include "Core/EngineContext.h"
#include "Core/EngineVisitor.h"

class Engine
{
private:
    friend EngineVisitor;

    sf::RenderWindow window_;
    EngineContext context_;
    
    void EventWindowClose();
    void EventWindowResized(sf::Vector2u size);
    void EventWindowFocusLost();
    void EventWindowFocusGained();
    void EventWindowScreenshot() const;
    void EventGamepadConnected(int id);
    void EventGamepadDisconnected(int id);

public:
    Engine();

    bool IsRunning() const;

    void ProcessEvents();
    void Update();
    void Render();
};