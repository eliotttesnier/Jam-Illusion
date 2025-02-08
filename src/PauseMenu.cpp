/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** PauseMenu
*/

#include "PauseMenu.hpp"
#include <iostream>

PauseMenu::PauseMenu() {
    font.loadFromFile("arial.ttf");
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

void PauseMenu::render(sf::RenderWindow& window) {
    window.draw(text);
}
