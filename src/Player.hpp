/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Player
*/

#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
public:
    Player();
    void update(sf::Time deltaTime);
    void handleInput(const sf::Event& event);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
    sf::Texture mTexture;

    float mSpeed;
};
