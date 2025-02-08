/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** PauseMenu
*/

#include "PauseMenu.hpp"
#include "Game.hpp"

PauseMenu::PauseMenu()
{
    _font.loadFromFile("assets/fonts/font.otf");

    _pauseText.setFont(_font);
    _pauseText.setString("Pause");
    _pauseText.setCharacterSize(100);
    _pauseText.setScale(sf::Vector2f(0.4,0.4));
    _pauseText.setFillColor(sf::Color::White);
    _pauseText.setPosition(1920 / 2 - _pauseText.getGlobalBounds().width / 2, 150);

    _resumeButton.setFont(_font);
    _resumeButton.setString("Resume");
    _resumeButton.setCharacterSize(80);
    _resumeButton.setFillColor(sf::Color::White);
    _resumeButton.setScale(sf::Vector2f(0.2,0.2));
    _resumeButton.setOutlineColor(sf::Color::Red);
    _resumeButton.setOutlineThickness(5);
    _resumeButton.setPosition(1920 / 2 - _resumeButton.getGlobalBounds().width / 2, 350);

    _quitButton.setFont(_font);
    _quitButton.setString("Quit");
    _quitButton.setCharacterSize(80);
    _quitButton.setFillColor(sf::Color::White);
    _quitButton.setScale(sf::Vector2f(0.2,0.2));
    _quitButton.setOutlineColor(sf::Color::Red);
    _quitButton.setOutlineThickness(5);
    _quitButton.setPosition(1920 / 2 - _quitButton.getGlobalBounds().width / 2, 450);
}

PauseMenu::~PauseMenu()
{

}

void PauseMenu::handleEvent(sf::Event& event, sf::RenderWindow& window, Game& game)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (_resumeButton.getGlobalBounds().contains(mousePos)) {
            game.setPause(false);
            game.setScene(GameState::GAME);
        } else if (_quitButton.getGlobalBounds().contains(mousePos)) {
            window.close();
        }
    }
}

void PauseMenu::update()
{

}

void PauseMenu::draw(sf::RenderWindow& window)
{
    sf::View view = window.getView();
    sf::Vector2f pos = view.getCenter();

    _pauseText.setPosition(pos.x - 40, pos.y - 125);
    _resumeButton.setPosition(pos.x - 20, pos.y - 50);
    _quitButton.setPosition(pos.x - 10, pos.y);
    _pauseText.setFont(_font);
    _resumeButton.setFont(_font);
    _quitButton.setFont(_font);
    window.draw(_pauseText);
    window.draw(_resumeButton);
    window.draw(_quitButton);
}
