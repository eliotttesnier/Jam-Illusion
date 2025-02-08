/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** IMenu
*/

#pragma once

#include <SFML/Graphics.hpp>
// #include "Game.hpp"
class Game;

class IMenu {
public:
    virtual ~IMenu() = default;
    virtual void handleEvent(sf::Event& event, sf::RenderWindow &window, Game& game) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};


