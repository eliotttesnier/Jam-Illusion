/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Object
*/

#include "Object.hpp"

Object::Object(sf::FloatRect triggerBox, std::string name)
{
    _triggerBox = triggerBox;
    _name = name;
}

Object::~Object()
{
}

bool Object::isColliding(const sf::FloatRect &other) const
{
    sf::FloatRect bottomHalf(other.left, other.top + other.height / 1.5, other.width, other.height / 1.5);

    return _triggerBox.intersects(bottomHalf);
}

std::string Object::getName() const
{
    return _name;
}
