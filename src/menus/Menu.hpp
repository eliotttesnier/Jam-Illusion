/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Menu
*/

#pragma once

#include "IMenu.hpp"
#include <vector>

class Menu : public IMenu {
    public:
        Menu();
        ~Menu();

        void handleEvent(sf::Event& event, GameState &state);
        void update(GameState &state, GameState newState);
        void draw(sf::RenderWindow& window);

    protected:
        sf::Font font;
        sf::Text title;
        std::vector<sf::Text> options;
        size_t selectedIndex;
        sf::RectangleShape background;
    private:

};
