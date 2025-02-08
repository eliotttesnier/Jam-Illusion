/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Exterior
*/

#include "Exterior.hpp"

Exterior::Exterior(int nextRoom) : Room()
{
    _texture.loadFromFile("assets/room/room0.png");
    _sprite.setTexture(_texture);
    _collisions.loadFromFile("assets/collision/room0_collision.png");
    _spawnPoint = sf::Vector2f(137, 180);
    _objects.push_back(Object(sf::FloatRect(133, 31, 21, 10), "Door", Object::Type::DOOR, nextRoom));
}

Exterior::~Exterior()
{
}
