/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Object
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Object {
    public:
        enum Type {
            DOOR,
            LIBRARY,
            BARREL,
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

        void scream();
        bool isScreaming() const;

        void barrelSound();

    protected:
    private:
        sf::FloatRect _triggerBox;
        std::string _name;
        Type _type;

        // Doors
        int _redirectTo;
        bool _isLocked;

        // Library
        sf::Texture _screamerTexture;
        sf::Sprite _screamerSprite;
        sf::Music _screamerSound;

        // Barrel
        sf::Music _barrelSound;

        // Animation
        sf::Sprite _sprite;
        sf::Texture _textures[5];
        int _currentFrame;
        sf::Clock _animationClock;
        sf::Clock _pauseClock;
        bool _isAnimating;
};
