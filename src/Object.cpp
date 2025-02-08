/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Object
*/

#include "Object.hpp"
#include <cstdarg>

Object::Object(sf::FloatRect triggerBox, std::string name, Type type, ...)
{
    _triggerBox = triggerBox;
    _name = name;
    _type = type;
    _redirectTo = 0;

    if (type == Type::DOOR) {
        va_list args;
        va_start(args, type);
        _redirectTo = va_arg(args, int);
        va_end(args);
    }
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

int Object::getRedirectTo() const
{
    return _redirectTo;
}

Object::Type Object::getType() const
{
    return _type;
}
