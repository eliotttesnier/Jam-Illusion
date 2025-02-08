/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Room
*/

#pragma once

#include "IRoom.hpp"

class Room : public IRoom {
    public:
        Room();
        ~Room();

        void draw(sf::RenderWindow &window);

        sf::Image getCollisions() const;
        std::vector<Object> getObjects() const;
        sf::Vector2f getSpawnPoint() const;

    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Image _collisions;
        std::vector<Object> _objects;
        sf::Vector2f _spawnPoint;
};
