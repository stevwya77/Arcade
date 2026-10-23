#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "Core/Overlay.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Err.hpp"
#include "SFML/System/Vector2.hpp"
#include "Utils/Log.h"
#include <cassert>


Engine::Engine() :
    window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)), gConfig.windowTitle),
    context_(window_),
    scenes_(SceneFactory::CreateScenes(context_)),
    currentScene_(nullptr),
    overlay_(context_.gui),
    cursorWasVisible_(true)
{
    window_.setIcon(sf::Image("Content/Textures/Icon.png"));
    window_.setMinimumSize(window_.getSize() / 2u);
    window_.setKeyRepeatEnabled(false);
    window_.setMouseCursorVisible(false);
    
    if (gConfig.disableSFMLLogs)
    {
        sf::err().rdbuf(nullptr);
    }

    context_.audio.SetGlobalVolume(gConfig.globalVolume);
    LOG_INFO("Window created");
    context_.scenes.ChangeScene("Bounce");
}

bool Engine::IsRunning() const
{
    return window_.isOpen();
}

bool Engine::HasFocus() const
{
    return window_.hasFocus();
}

void Engine::ProcessEvents()
{
    if (const auto nextScene = context_.scenes.FetchNextScene())
    {
        EventSceneChange(*nextScene);
    }

    while (const auto event = window_.pollEvent())
    {
        event->visit(EngineVisitor{*this});
        context_.gui.ProcessEvent(*event);

        if (!overlay_.IsVisible())
        {
            currentScene_->OnEvent(*event);
        }
    }

    if (const auto selection = overlay_.FetchSelection())
    {
        EventOverlaySelect(*selection);
    }
}

void Engine::Update()
{
    context_.time.Update();
    context_.cursor.Update(context_.time.GetDeltaTime());
    if (!overlay_.IsVisible())
    {
        currentScene_->Update();
    }
}

void Engine::Render()
{
    window_.clear();
    
    context_.renderer.BeginDrawing();
    currentScene_->Render();
    window_.draw(sf::Sprite(context_.renderer.FinishDrawing()));
    
    context_.gui.Render();
    context_.cursor.Render();

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
    currentScene_->OnPause(true);
    LOG_INFO("Window focus lost");
}

void Engine::EventWindowFocusGained()
{
    currentScene_->OnPause(overlay_.IsVisible());
    LOG_INFO("Window focus gained");
}

void Engine::EventWindowScreenshot() const
{
    context_.screenshot.Take();
}

void Engine::EventGamepadConnected(int id)
{
    LOG_INFO("Gamepad {} connected", id);
}

void Engine::EventGamepadDisconnected(int id)
{
    LOG_INFO("Gamepad {} disconnected", id);
}

void Engine::EventSceneChange(const std::string& name)
{
    assert(scenes_.contains(name));
    Scene* nextScene = scenes_.at(name).get();

    if (currentScene_)
    {
        currentScene_->OnCleanUp();
    }

    context_.input.Clear();

    currentScene_ = nextScene;
    currentScene_->Start();
}

void Engine::EventSceneRestart()
{
    overlay_.SetVisible(false);
    context_.scenes.RestartCurrentScene();
}

void Engine::EventSceneMenuReturn()
{
    overlay_.SetVisible(false);
    context_.scenes.ChangeScene("Menu");
    
    context_.cursor.SetVisible(true);
    context_.cursor.SetSpeed(gConfig.cursorSpeed);
}

void Engine::EventOverlayPauseToggle()
{
    const bool overlayVisible = !overlay_.IsVisible();
    overlay_.SetVisible(overlayVisible);

    const bool cursorVisible = context_.cursor.IsVisible();
    context_.cursor.SetVisible(overlayVisible || cursorWasVisible_);
    cursorWasVisible_ = cursorVisible;

    currentScene_->OnPause(overlayVisible);
    LOG_INFO(overlayVisible ? "Game paused" : "Game resumed");
}

void Engine::EventOverlaySelect(OverlaySelection selection)
{
    switch (selection) 
    {
        case OverlaySelection::Resume: EventOverlayPauseToggle(); break;
        case OverlaySelection::Restart: EventSceneRestart(); break;
        case OverlaySelection::Menu: EventSceneMenuReturn(); break;
        case OverlaySelection::Quit: EventWindowClose(); break;
        default: break;
    }
}