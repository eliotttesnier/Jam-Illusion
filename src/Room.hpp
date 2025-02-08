/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Room
*/

#pragma once

#include <SFML/Graphics.hpp>

class Room {
    public:
        Room(int id);
        ~Room();

        void draw(sf::RenderWindow &window);

        sf::Image getCollisions() const;

    protected:
    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Image _collisions;
};
