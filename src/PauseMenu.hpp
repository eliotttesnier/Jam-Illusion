/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** PauseMenu
*/

#pragma once

#include "IMenu.hpp"

class PauseMenu : public IMenu {
private:
    sf::Font font;
    sf::Text text;

public:
    PauseMenu();
    void handleEvent(sf::Event& event, sf::RenderWindow &window, Game& game) override;
    void update() override {}
    void draw(sf::RenderWindow& window) override;
};
