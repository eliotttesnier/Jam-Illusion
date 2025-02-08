/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** MainMenu
*/

#pragma once

#include "IMenu.hpp"
#include <vector>

class MainMenu : public IMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
    size_t selectedIndex;

public:
    MainMenu();
    void handleEvent(sf::Event& event) override;
    void update() override {}
    void render(sf::RenderWindow& window) override;
};


