/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Exterior
*/

#include "Exterior.hpp"
#include <iostream>
#include <stdexcept>

Exterior::Exterior(int nextRoom) : Room() {
    const std::string texturePath = "assets/room/room0.png";
    const std::string collisionPath = "assets/collision/room0_collision.png";

    if (!validatePaths(texturePath, collisionPath)) {
        throw std::runtime_error("Required asset files are missing");
    }

    if (!loadTexture(texturePath)) {
        throw std::runtime_error("Failed to load room texture");
    }

    if (!loadCollisionMap(collisionPath)) {
        throw std::runtime_error("Failed to load collision map");
    }

    _spawnPoint = sf::Vector2f(137, 180);
    
    try {
        _objects.push_back(Object(sf::FloatRect(133, 31, 21, 10), "Door", Object::Type::DOOR, nextRoom));
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to initialize room objects: ") + e.what());
    }
}

Exterior::~Exterior()
{
}
