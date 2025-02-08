/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::handleEvent(sf::Event& event, GameState &state)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : options.size() - 1;
            std::cout << "Option sélectionnée : " << options[selectedIndex].getString().toAnsiString() << std::endl;
        } 
        if (event.key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex < options.size() - 1) ? selectedIndex + 1 : 0;
            std::cout << "Option sélectionnée : " << options[selectedIndex].getString().toAnsiString() << std::endl;
        } 
        if (event.key.code == sf::Keyboard::Enter) {
            if (selectedIndex == 0) {
                std::cout << "Lancement du jeu..." << std::endl;
                update(state, GameState::GAME);
            }
            if (selectedIndex == 1) {
                std::cout << "Paramètres..." << std::endl;
                // à modifier
                update(state, GameState::GAME);
            } 
            if (selectedIndex == 2) {
                std::cout << "Fermeture du jeu..." << std::endl;
                exit(0);
            }
        }
    }
}

void Menu::update(GameState &state, GameState newState)
{
    if (state != newState)
        state = newState;
}

void Menu::draw(sf::RenderWindow& window)
{
    background.setSize(sf::Vector2f(1920, 1080));
    background.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(background);
    for (size_t i = 0; i < options.size(); i++) {
        options[i].setFillColor(i == selectedIndex ? sf::Color::Red : sf::Color::White);
        window.draw(options[i]);
    }
}
