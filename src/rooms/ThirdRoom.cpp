/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** ThirdRoom
*/

#include "ThirdRoom.hpp"

ThirdRoom::ThirdRoom(int nextRoom) : Room()
{
    _texture.loadFromFile("assets/room/room3.png");
    _sprite.setTexture(_texture);
    _collisions.loadFromFile("assets/collision/room3_collision.png");
    _spawnPoint = sf::Vector2f(264, 25);
    _objects.push_back(new Object(sf::FloatRect(261, 31, 21, 10), "Door", Object::Type::DOOR, nextRoom, true));
    _objects.push_back(new Object(sf::FloatRect(6, 95, 29, 30), "Barrel", Object::Type::BARREL));
    sf::Vector2f randomPos = generateRandomPosition();
    _pnjs.push_back(new PNJ(randomPos, "dialogues/room05.txt"));
}

ThirdRoom::~ThirdRoom()
{
}
