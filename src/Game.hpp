/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Game
*/

#pragma once

#include "Player.hpp"
#include "Room.hpp"
#include "MainMenu.hpp"

class Game {
    public:
        enum SCENE {
            MAIN_MENU,
            GAME
        };

        Game();
        ~Game();

        // Methods
        void run();
        void update();
        void draw();

    protected:
    private:
        // Scene logic
        SCENE _currentScene;

        Player _player;

        // Graphics
        sf::RenderWindow _window;
        sf::View _view;
        sf::Event _event;
        sf::Clock _clock;
        float _deltaTime;

        // Rooms
        int _currentRoom;
        std::vector<Room> _rooms;

        // Menus
        MainMenu _mainMenu;
};
