#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "SFML/System/Err.hpp"
#include "SFML/System/Vector2.hpp"
#include "Utils/Log.h"


Engine::Engine() :
    window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)), gConfig.windowTitle)
{
    window_.setIcon(sf::Image("Content/Textures/Icon.png"));
    window_.setMinimumSize(window_.getSize() / 2u);

    if (gConfig.disableSFMLLogs)
    {
        sf::err().rdbuf(nullptr);
    }

    LOG_INFO("Window created");

}

bool Engine::IsRunning() const
{
    return window_.isOpen();
}

void Engine::ProcessEvents()
{
    while (const auto event = window_.pollEvent())
    {
        event->visit(EngineVisitor{*this});
    }
}

void Engine::Update()
{
    context_.time.Update();
}

void Engine::Render()
{
    window_.clear();
    window_.display();
}

void Engine::EventWindowClose()
{
    window_.close();
    LOG_INFO("Window closed");
}

void Engine::EventWindowResized(sf::Vector2u size)
{
    LOG_INFO("Window resized to: {}x{}", size.x, size.y);
}

void Engine::EventWindowFocusLost()
{
    LOG_INFO("Window focus lost");
}

void Engine::EventWindowFocusGained()
{
    LOG_INFO("Window focus gained");
}