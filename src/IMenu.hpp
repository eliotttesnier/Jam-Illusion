/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** IMenu
*/

#pragma once

#include <SFML/Graphics.hpp>

class IMenu {
public:
    virtual ~IMenu() = default;
    virtual void handleEvent(sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};


