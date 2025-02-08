/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Room
*/

#include "Room.hpp"

Room::Room(int id)
{
    _texture.loadFromFile("assets/room/room" + std::to_string(id) + ".png");
    _sprite.setTexture(_texture);
    _collisions.loadFromFile("assets/collision/room" + std::to_string(id) + "_collision.png");
}

Room::~Room()
{
}

// Methods
void Room::draw(sf::RenderWindow &window)
{
    _sprite.setTexture(_texture);
    window.draw(_sprite);
}

// Getters
sf::Image Room::getCollisions() const
{
    return _collisions;
}
