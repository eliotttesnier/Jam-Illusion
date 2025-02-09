/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Final
*/

#include "Final.hpp"

Final::Final() : Room()
{
    _texture.loadFromFile("assets/room/room5.png");
    _sprite.setTexture(_texture);
    _collisions.loadFromFile("assets/collision/room5_collision.png");
    _spawnPoint = sf::Vector2f(167, 125);
    _objects.push_back(new Object(sf::FloatRect(256, 167, 63, 56), "Bed", Object::Type::BED));
}

Final::~Final()
{
}
