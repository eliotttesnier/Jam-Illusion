/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** PauseMenu
*/

#include "PauseMenu.hpp"
#include <iostream>

PauseMenu::PauseMenu() {
    if (!font.loadFromFile("assets/fonts/font.otf")) {
        std::cerr << "Error loading font in PauseMenu" << std::endl;
        return;
    }
    text.setFont(font);
    text.setString("Pause\nAppuyez sur Échap pour reprendre");
    text.setCharacterSize(40);
    text.setPosition(200, 200);
}

void PauseMenu::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        std::cout << "Reprise du jeu..." << std::endl;
    }
}

void PauseMenu::draw(sf::RenderWindow& window) {
    window.draw(text);
}
