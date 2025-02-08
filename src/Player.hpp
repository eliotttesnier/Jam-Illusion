/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Player
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

class Player {
    public:
        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            IDLE
        };

        // Constructor
        Player();
        ~Player();

        // Methods
        void update(float deltaTime, const sf::Image &collisions);
        void handleInput();
        void move(float deltaTime);
        void CheckCollisions(const sf::Image &collisions, float deltaTime);
        void animate(float deltaTime);
        void draw(sf::RenderWindow &window);

        // Getters
        sf::Vector2f getPosition() const;
        sf::Vector2f getCenter() const;
        float getSpeed() const;
        const sf::Sprite &getSprite() const;

        // Setters
        void setPosition(const sf::Vector2f &position);
        void setSpeed(float speed);

    protected:
    private:
        // Logic
        sf::Vector2f _position;
        sf::Vector2f _direction;
        Direction _currentDirection;
        float _speed;

        // Graphics
        sf::Sprite _sprite;
        std::map<Direction, std::vector<sf::Texture>>_textures;
        sf::Clock _animationClock;
        int _currentFrame;
};
