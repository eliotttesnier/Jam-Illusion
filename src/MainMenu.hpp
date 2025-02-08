/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** MainMenu
*/

#pragma once

#include "IMenu.hpp"
#include <SFML/Graphics.hpp>

class MainMenu : public IMenu {
    public:
        MainMenu();
        ~MainMenu();

        // Method
        void handleEvent(sf::Event& event, sf::RenderWindow &window, Game& game) override;
        void update() override;
        void draw(sf::RenderWindow& window) override;

    private:
        sf::Text _title;
        sf::Text _playButton;
        sf::Text _quitButton;
        sf::Font _font;
};
