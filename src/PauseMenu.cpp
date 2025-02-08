/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** PauseMenu
*/

#include "PauseMenu.hpp"
#include "FontManager.hpp"
#include <iostream>

PauseMenu::PauseMenu() {
    sf::Font* font = FontManager::getInstance().getFont("assets/fonts/font.otf");
    if (!font) {
        throw std::runtime_error("Failed to load font");
    }
    text.setFont(*font);
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
