/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

MainMenu::MainMenu() {
    // Charger la police
    _font.loadFromFile("assets/fonts/font.otf");

    // Initialiser le titre
    _title.setFont(_font);
    _title.setString("Jamy-llusion");
    _title.setCharacterSize(100);
    _title.setFillColor(sf::Color::White);
    _title.setPosition(1920 / 2 - _title.getGlobalBounds().width / 2, 150);

    // Initialiser le bouton Play
    _playButton.setFont(_font);
    _playButton.setString("Play");
    _playButton.setCharacterSize(50);
    _playButton.setFillColor(sf::Color::White);
    _playButton.setOutlineColor(sf::Color::Red);
    _playButton.setPosition(1920 / 2 - _playButton.getGlobalBounds().width / 2, 350);
    _playButton.setOutlineThickness(5);
}

MainMenu::~MainMenu() {}

void MainMenu::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
        }
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (_playButton.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
                _playButton.setFillColor(sf::Color::Green);
        }
    }
}

void MainMenu::update()
{

}

void MainMenu::draw(sf::RenderWindow& window) {
    _title.setFont(_font);
    window.draw(_title);
    _playButton.setFont(_font);
    window.draw(_playButton);
}
