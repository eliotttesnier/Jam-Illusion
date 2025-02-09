/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Gameover
*/

#pragma once

#include <SFML/Graphics.hpp>

class ScreenFade {
    public:
        ScreenFade(sf::RenderWindow &window, sf::View &view);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        bool isFinished() const;

    private:
        sf::RenderTexture _renderTexture;
        sf::Sprite _renderSprite;
        sf::CircleShape _topArc;
        sf::CircleShape _bottomArc;
        sf::Font _font;
        sf::Text _gameOverText;
        sf::Vector2u _windowSize;
        float _animationProgress;
        bool _animationFinished;
};
