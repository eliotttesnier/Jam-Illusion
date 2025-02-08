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
    _objects.push_back(new Object(sf::FloatRect(133, 31, 21, 10), "Door", Object::Type::DOOR, nextRoom, true));
    sf::Vector2f randomPos = generateRandomPosition();
    if (nextRoom == 2)
        _pnjs.push_back(new PNJ(randomPos, "dialogues/room01.txt"));
    else if (nextRoom == 4)
        _pnjs.push_back(new PNJ(randomPos, "dialogues/room04.txt"));
    else if (nextRoom == 8)
        _pnjs.push_back(new PNJ(randomPos, "dialogues/room08.txt"));
    else if (nextRoom == 9)
        _pnjs.push_back(new PNJ(randomPos, "dialogues/room09.txt"));
    else if (nextRoom == 10)
        _pnjs.push_back(new PNJ(randomPos, "dialogues/room10.txt"));
    else if (nextRoom == 11)
        _pnjs.push_back(new PNJ(randomPos, "dialogues/room11.txt"));
}

FirstRoom::~FirstRoom()
{
}
