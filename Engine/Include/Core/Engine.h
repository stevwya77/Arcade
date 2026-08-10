#pragma once
#include "Core/EngineVisitor.h"
#include <SFML/Graphics.hpp>

class Engine
{
private:
    friend EngineVisitor;

    sf::RenderWindow window_;
    
    void EventWindowClose();
public:
    Engine();

    bool IsRunning() const;

    void ProcessEvents();
    void Update();
    void Render();
};