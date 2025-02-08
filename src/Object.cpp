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
    return _triggerBox.intersects(other);
}

std::string Object::getName() const
{
    return _name;
}
