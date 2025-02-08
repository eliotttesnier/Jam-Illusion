/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Object
*/

#pragma once

#include <SFML/Graphics.hpp>

class Object {
    public:
        Object(sf::FloatRect triggerBox, std::string name);
        ~Object();

        bool isColliding(const sf::FloatRect &other) const;

        std::string getName() const;

    protected:
    private:
        sf::FloatRect _triggerBox;
        std::string _name;
};
