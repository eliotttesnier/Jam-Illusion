/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Gameover
*/

#include "GameOver.hpp"
#include <iostream>

ScreenFade::ScreenFade(sf::RenderWindow& window, sf::View& view)
{
    _windowSize = window.getSize();
    _renderTexture.create(_windowSize.x, _windowSize.y);
    _renderSprite.setTexture(_renderTexture.getTexture());

    float radius = std::max(_windowSize.x, _windowSize.y) * 1.5f;

    // Arc du haut
    _topArc.setRadius(radius);
    _topArc.setPointCount(100);
    _topArc.setFillColor(sf::Color::Red);
    _topArc.setOrigin(radius, radius);
    _topArc.setPosition(_windowSize.x / 2, _windowSize.y / 2 - radius / 2);

    // Arc du bas (miroir du haut)
    _bottomArc.setRadius(radius);
    _bottomArc.setPointCount(100);
    _bottomArc.setFillColor(sf::Color::Red);
    _bottomArc.setOrigin(radius, radius);
    _bottomArc.setPosition(_windowSize.x / 2, _windowSize.y / 2 + radius / 2);
    _bottomArc.setRotation(180);

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
        _windowSize.x / 2 - _gameOverText.getGlobalBounds().width / 2,
        _windowSize.y / 2 - _gameOverText.getGlobalBounds().height / 2
    );

    _animationProgress = 0.0f;
    _animationFinished = false;
}


void ScreenFade::update(float deltaTime)
{
    if (_animationFinished) return;
    std::cout << "deltaTime: " << deltaTime << " | Progress: " << _animationProgress << std::endl;
    _animationProgress += deltaTime * 0; // Ajuste la vitesse de fermeture
    std::cout << "New _animationProgress: " << _animationProgress << std::endl;
    // Faire descendre uniquement l'arc du bas
    float bottomY = _bottomArc.getPosition().y + _animationProgress;

    std::cout << bottomY << std::endl;
    if (_animationProgress >= _windowSize.y / 2) {
        _animationFinished = true;
        _gameOverText.setFillColor(sf::Color(255, 0, 0, 255));
    }

    _bottomArc.setPosition(_bottomArc.getPosition().x, bottomY);
}

void ScreenFade::draw(sf::RenderWindow& window)
{
    _renderTexture.clear(sf::Color::Transparent);
    _renderTexture.draw(_topArc);   // Ne bouge pas
    _renderTexture.draw(_bottomArc); // Descend progressivement
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
