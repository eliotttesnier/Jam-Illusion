/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Object
*/

#include "Object.hpp"
#include <cstdarg>
#include <iostream>

Object::Object(sf::FloatRect triggerBox, std::string name, Type type, ...)
{
    _triggerBox = triggerBox;
    _name = name;
    _type = type;
    _redirectTo = 0;
    _currentFrame = 0;
    _isAnimating = true;

    if (type == Type::DOOR) {
        va_list args;
        va_start(args, type);
        _redirectTo = va_arg(args, int);
        _isLocked = va_arg(args, int);
        va_end(args);
    }

    if (type == Type::LIBRARY) {
        _screamerTexture.loadFromFile("assets/images/screamer.png");
        _screamerSprite.setTexture(_screamerTexture);
        _screamerSprite.setScale(sf::Vector2f(0.5, 0.5));
        _screamerSound.openFromFile("assets/music/screamer.wav");
    }

    for (int i = 0; i <= 4; ++i) {
        if (!_textures[i].loadFromFile("assets/animation/animation" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Erreur de chargement de l'image interaction" << i + 1 << ".png" << std::endl;
        }
    }
    _textures[4].setSmooth(true);
    _sprite.setTexture(_textures[0]);
    _sprite.setScale(sf::Vector2f(0.5, 0.5));
}

Object::~Object()
{
}

bool Object::isColliding(const sf::FloatRect &other) const
{
    sf::FloatRect bottomHalf(other.left, other.top + other.height / 1.5, other.width, other.height / 1.5);

    return _triggerBox.intersects(bottomHalf);
}

void Object::update()
{
    if (_isAnimating) {
        if (_animationClock.getElapsedTime().asSeconds() >= 0.1f) {
            _sprite.setPosition(sf::Vector2f(_triggerBox.left + 10, _triggerBox.top - 20));
            _currentFrame = (_currentFrame + 1) % 5;
            _sprite.setTexture(_textures[_currentFrame]);
            _animationClock.restart();

            if (_currentFrame == 4) {
                _sprite.setPosition(sf::Vector2f(10000, 10000));
                _isAnimating = false;
                _pauseClock.restart();
            }
        }
    } else {
        if (_pauseClock.getElapsedTime().asSeconds() >= 3.0f) {
            _isAnimating = true;
            _currentFrame = 0;
            _sprite.setTexture(_textures[_currentFrame]);
            _animationClock.restart();
        }
    }
}

void Object::draw(sf::RenderWindow &window)
{
    _sprite.setTexture(_textures[_currentFrame]);
    window.draw(_sprite);

    if (_type == Type::LIBRARY && isScreaming()) {
        sf::View view = window.getView();

        _screamerSprite.setScale(
            view.getSize().x / _screamerSprite.getLocalBounds().width,
            view.getSize().y / _screamerSprite.getLocalBounds().height
        );
        _screamerSprite.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
        window.draw(_screamerSprite);
    }
}

std::string Object::getName() const
{
    return _name;
}

int Object::getRedirectTo() const
{
    return _redirectTo;
}

Object::Type Object::getType() const
{
    return _type;
}

bool Object::isLocked() const
{
    return _isLocked;
}

void Object::unlock()
{
    _isLocked = false;
}

void Object::scream()
{
    _screamerSound.setVolume(100);
    _screamerSound.stop();
    _screamerSound.play();
}

bool Object::isScreaming() const
{
    return _screamerSound.getStatus() == sf::Music::Playing;
}
