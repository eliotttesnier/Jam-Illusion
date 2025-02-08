/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Gameover
*/

#include "GameOver.hpp"
#include <iostream>

ScreenFade::ScreenFade(sf::Vector2u windowSize)
{
    _renderTexture.create(windowSize.x, windowSize.y);
    _renderSprite.setTexture(_renderTexture.getTexture());

    float radius = windowSize.x * 0.8f;
    _topArc.setRadius(radius);
    _topArc.setPointCount(100);
    _topArc.setFillColor(sf::Color::Black);
    _topArc.setOrigin(radius, radius);
    _topArc.setPosition(windowSize.x / 2, -radius / 2);

    _bottomArc.setRadius(radius);
    _bottomArc.setPointCount(100);
    _bottomArc.setFillColor(sf::Color::Black);
    _bottomArc.setOrigin(radius, radius);
    _bottomArc.setPosition(windowSize.x / 2, windowSize.y + radius / 2);

    if (!_font.loadFromFile("assets/fonts/font.otf")) {
        std::cerr << "Erreur: Impossible de charger la police" << std::endl;
    }

    _gameOverText.setFont(_font);
    _gameOverText.setString("GAME OVER");
    _gameOverText.setCharacterSize(100);
    _gameOverText.setFillColor(sf::Color(255, 0, 0, 0));
    _gameOverText.setOutlineColor(sf::Color::Black);
    _gameOverText.setOutlineThickness(5);
    _gameOverText.setPosition(
        windowSize.x / 2 - _gameOverText.getGlobalBounds().width / 2,
        windowSize.y / 2 - _gameOverText.getGlobalBounds().height / 2
    );

    _animationProgress = 0.0f;
    _animationFinished = false;
}

void ScreenFade::update(float deltaTime)
{
    if (_animationFinished) return;

    _animationProgress += deltaTime * 300;

    _topArc.setPosition(_topArc.getPosition().x, -_topArc.getRadius() + _animationProgress);
    _bottomArc.setPosition(_bottomArc.getPosition().x, _bottomArc.getRadius() - _animationProgress + _renderTexture.getSize().y);

    if (_topArc.getPosition().y >= 0 && _bottomArc.getPosition().y <= _renderTexture.getSize().y) {
        _animationFinished = true;
        _gameOverText.setFillColor(sf::Color(255, 0, 0, 255));
    }
}

void ScreenFade::draw(sf::RenderWindow& window)
{
    _renderTexture.clear(sf::Color::Transparent);
    _renderTexture.draw(_topArc);
    _renderTexture.draw(_bottomArc);
    if (_animationFinished) {
        _renderTexture.draw(_gameOverText);
    }
    _renderTexture.display();

    window.draw(_renderSprite);
}

bool ScreenFade::isFinished() const
{
    return _animationFinished;
}
