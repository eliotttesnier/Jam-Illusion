/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Gameover
*/

#include "GameOver.hpp"
#include <iostream>

ScreenFade::ScreenFade(sf::RenderWindow &window, sf::View &view)
    : _animationProgress(0.f), _animationFinished(false)
{

    if (!_eyeTexture.loadFromFile("assets/animation/eyes.png")) {
        std::cerr << "Erreur de chargement du sprite des yeux!" << std::endl;
    }

    _windowSize = window.getSize();

    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    float zoomFactor = 0.25;
    float initialPositionYTop = viewCenter.y - _eyeTexture.getSize().y / 2 * zoomFactor;
    float initialPositionYBottom = viewCenter.y + viewSize.y / 2 * 0.25 - _eyeTexture.getSize().y;

    _topEye.setTexture(_eyeTexture);
    _topEye.setPosition(viewCenter.x - 25, -175);
    _topEye.setOrigin(_eyeTexture.getSize().x / 2, _eyeTexture.getSize().y / 2);

    _bottomEye.setTexture(_eyeTexture);
    _bottomEye.setPosition(viewCenter.x - 25, 475);
    _bottomEye.setOrigin(_eyeTexture.getSize().x / 2, _eyeTexture.getSize().y / 2);
    sf::Vector2f topScale = _topEye.getScale();
    _bottomEye.setScale(topScale.x, -topScale.y);

    _windowSize = window.getSize();
}

void ScreenFade::update(float deltaTime)
{
    if (_animationFinished)
        return;

    float targetY = 250;
    float moveSpeed = 100.f * deltaTime;

    if (_topEye.getPosition().y < targetY - 100) {
        _topEye.move(0.f, moveSpeed);
    }

    if (_bottomEye.getPosition().y > targetY - 100) {
        _bottomEye.move(0.f, -moveSpeed);
    }

    if (_topEye.getPosition().y >= targetY && _bottomEye.getPosition().y <= targetY) {
        _animationFinished = true;
    }
}

void ScreenFade::draw(sf::RenderWindow &window)
{
    window.draw(_topEye);
    window.draw(_bottomEye);
}

bool ScreenFade::isFinished() const
{
    return _animationFinished;
}
