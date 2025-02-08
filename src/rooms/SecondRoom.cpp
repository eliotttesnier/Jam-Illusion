/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** SecondRoom
*/

#include "SecondRoom.hpp"

SecondRoom::SecondRoom()
{
    _texture.loadFromFile("assets/room/room2.png");
    _sprite.setTexture(_texture);
    _collisions.loadFromFile("assets/collision/room2_collision.png");
    _spawnPoint = sf::Vector2f(40, 25);
    _objects.push_back(Object(sf::FloatRect(37, 31, 21, 10), "Door", Object::Type::DOOR, 3));
}

SecondRoom::~SecondRoom()
{
}
