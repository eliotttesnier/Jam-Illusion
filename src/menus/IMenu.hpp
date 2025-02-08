/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** IMenu
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "../GameState.hpp"

class IMenu
{
    public:
        virtual ~IMenu() = default;
        virtual void handleEvent(sf::Event& event, GameState &state) = 0;
        virtual void update(GameState &state, GameState newState) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
};
