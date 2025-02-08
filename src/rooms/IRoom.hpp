/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** IRoom
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Object.hpp"

class IRoom {
    public:
        virtual ~IRoom() = default;

        virtual void draw(sf::RenderWindow &window) = 0;

        virtual sf::Image getCollisions() const = 0;
        virtual std::vector<Object> getObjects() const = 0;
        virtual sf::Vector2f getSpawnPoint() const = 0;

    protected:
    private:
};
