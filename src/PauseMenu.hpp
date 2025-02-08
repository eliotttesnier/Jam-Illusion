/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** PauseMenu
*/

#pragma once

#include "IMenu.hpp"
#include <SFML/Graphics.hpp>

class PauseMenu : public IMenu {
    public:
        PauseMenu();
        ~PauseMenu();

        void handleEvent(sf::Event& event, sf::RenderWindow &window, Game& game) override;
        void update() override;
        void draw(sf::RenderWindow& window) override;

    private:
        sf::Text _pauseText;
        sf::Text _resumeButton;
        sf::Text _quitButton;
        sf::Font _font;
};
