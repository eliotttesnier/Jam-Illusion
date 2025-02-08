/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Game
*/

#pragma once

#include "Player.hpp"

class Game {
    public:
        Game();
        ~Game();

        // Methods
        void run();
        void update();
        void draw();

    protected:
    private:
        Player _player;

        // Graphics
        sf::RenderWindow _window;
        sf::View _view;
        sf::Event _event;
        sf::Clock _clock;
        float _deltaTime;
};
