#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Core/EngineContext.h"
#include "Core/EngineVisitor.h"
#include "Scene/SceneFactory.h"
#include "Core/Overlay.h"

class Engine
{
private:
    friend EngineVisitor;

    sf::RenderWindow window_;
    EngineContext context_;
    SceneFactory::Scenes scenes_;
    Scene* currentScene_;
    Overlay overlay_;
    
    bool cursorWasVisible_;
    void EventWindowClose();
    void EventWindowResized(sf::Vector2u size);
    void EventWindowFocusLost();
    void EventWindowFocusGained();
    void EventWindowScreenshot() const;
    void EventGamepadConnected(int id);
    void EventGamepadDisconnected(int id);
    void EventSceneChange(const std::string& name);
    void EventSceneRestart();
    void EventSceneMenuReturn();
    void EventOverlayPauseToggle();
    void EventOverlaySelect(OverlaySelection selection);

public:
    Engine();

    bool IsRunning() const;
    bool HasFocus() const;

    void ProcessEvents();
    void Update();
    void Render();
};