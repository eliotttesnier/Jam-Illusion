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

    // Implémentation des méthodes de l'interface IMenu
    void handleEvent(sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text _title;
    sf::Text _playButton;
    sf::Font _font;
};
