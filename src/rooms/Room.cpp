/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Room
*/

#include "Room.hpp"

Room::Room()
{
}

Room::~Room()
{
}

// Methods
void Room::draw(sf::RenderWindow &window)
{
    _sprite.setTexture(_texture);
    window.draw(_sprite);
    for (auto &pnj : _pnjs) {
        pnj->draw(window);
    }
}

// Getters
sf::Image Room::getCollisions() const
{
    return _collisions;
}

std::vector<Object> Room::getObjects() const
{
    return _objects;
}

sf::Vector2f Room::getSpawnPoint() const
{
    return _spawnPoint;
}

std::vector<PNJ *> Room::getPNJs() const
{
    return _pnjs;
}
