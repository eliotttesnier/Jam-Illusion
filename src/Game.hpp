/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Game
*/

#pragma once

#include "Player.hpp"
#include "IRoom.hpp"
#include "Room.hpp"
#include "Object.hpp"
#include "MainMenu.hpp"
#include "pnj.hpp"
#include "PauseMenu.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Music.hpp"

enum class GameState { MAIN_MENU, GAME, PAUSE };

class Game
{
    public:
        Game();
        ~Game();

        // Methods
        void run();
        void processEvents();
        void update();
        void draw();

        // Getters
        int getCurrentRoom() const;
        std::vector<IRoom *> getRooms() const;
        sf::Music::Status getNarrationStatus() const;
        bool getScreaming() const;

        // Setters
        void setCurrentRoom(int currentRoom);
        void setScreaming(bool screaming);

    protected:
    private:
        // Scene logic
        GameState _currentScene;
        IMenu* _currentMenu;
        Music _music;
        Player _player;

        // Graphics
        sf::RenderWindow _window;
        sf::View _view;
        sf::Event _event;
        sf::Clock _clock;
        float _deltaTime;

        // Rooms
        int _currentRoom;
        std::vector<IRoom *> _rooms;
        std::vector<std::unique_ptr<sf::Music>> _narrations;

        // Menus
        MainMenu _mainMenu;
        PauseMenu _pauseMenu;

        // Interactions HUD
        bool _canInteract;
        sf::Text _interactText;
        sf::Font _interactFont;
        bool _screaming;
};
