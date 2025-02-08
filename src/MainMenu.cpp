/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** MainMenu
*/

#include "MainMenu.hpp"
#include "Game.hpp"

MainMenu::MainMenu()
{
    _font.loadFromFile("assets/fonts/font.otf");

    _title.setFont(_font);
    _title.setString("Jamy-llusion");
    _title.setCharacterSize(100);
    _title.setFillColor(sf::Color::White);
    _title.setPosition(1920 / 2 - _title.getGlobalBounds().width / 2, 150);

    _playButton.setFont(_font);
    _playButton.setString("Play");
    _playButton.setCharacterSize(50);
    _playButton.setFillColor(sf::Color::White);
    _playButton.setOutlineColor(sf::Color::Red);
    _playButton.setPosition(1920 / 2 - _playButton.getGlobalBounds().width / 2, 350);
    _playButton.setOutlineThickness(5);
}


MainMenu::~MainMenu() {}

void MainMenu::handleEvent(sf::Event& event, sf::RenderWindow& window, Game& game) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (_playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                game.setScene(GameState::GAME);
            }
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
