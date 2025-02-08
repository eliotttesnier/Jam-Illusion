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
        enum Type {
            DOOR,
            NPC,
            ITEM
        };

        Object(sf::FloatRect triggerBox, std::string name, Type type = Type::DOOR, ...);
        ~Object();

        // Methods
        bool isColliding(const sf::FloatRect &other) const;
        void update();
        void draw(sf::RenderWindow &window);

        // Getters
        std::string getName() const;
        int getRedirectTo() const;
        Type getType() const;
        bool isLocked() const;

        void unlock();

    protected:
    private:
        sf::FloatRect _triggerBox;
        std::string _name;
        Type _type;

        // Doors
        int _redirectTo;
        bool _isLocked;

        // Animation
        sf::Sprite _sprite;
        sf::Texture _textures[5];
        int _currentFrame;
        sf::Clock _animationClock;
        sf::Clock _pauseClock;
        bool _isAnimating;
};
