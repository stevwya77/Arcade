#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics.hpp>

class RenderManager
{
private:
    sf::RenderTexture target_;
    sf::Texture backgroundTexture_;
    sf::RectangleShape background_;

public:
    RenderManager();
    void Draw(const sf::Drawable& drawable);
    void SetView(const sf::View& view);
    void ResetView();

private:
    friend class Engine;
    
    void BeginDrawing();
    const sf::Texture& FinishDrawing();
};
