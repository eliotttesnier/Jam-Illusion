/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** FourthRoom
*/

#include "FourthRoom.hpp"

FourthRoom::FourthRoom(int nextRoom) : Room()
{
    _texture.loadFromFile("assets/room/room4.png");
    _sprite.setTexture(_texture);
    _collisions.loadFromFile("assets/collision/room4_collision.png");
    _spawnPoint = sf::Vector2f(136, 25);
    _objects.push_back(new Object(sf::FloatRect(133, 31, 21, 10), "Door", Object::Type::DOOR, nextRoom, false));
}

FourthRoom::~FourthRoom()
{
}
