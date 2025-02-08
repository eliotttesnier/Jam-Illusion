/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** FirstRoom
*/

#include "FirstRoom.hpp"

FirstRoom::FirstRoom(int nextRoom) : Room()
{
    _texture.loadFromFile("assets/room/room1.png");
    _sprite.setTexture(_texture);
    _collisions.loadFromFile("assets/collision/room1_collision.png");
    _spawnPoint = sf::Vector2f(137, 28);
    _objects.push_back(Object(sf::FloatRect(133, 31, 21, 10), "Door", Object::Type::DOOR, nextRoom));
    _pnjs.push_back(new PNJ(sf::Vector2f(50, 50), "dialogues/room0.txt"));
}

FirstRoom::~FirstRoom()
{
}
