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
#include "PauseMenu.hpp"
#include "pnj.hpp"
#include <SFML/Graphics.hpp>
#include "Music.hpp"
#include <SFML/Audio.hpp>
#include <memory>

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
        void setScene(GameState scene);
        void setScreaming(bool screaming);
        void setPause(bool pause);

        void playEnding();

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
        bool ispaused;

        // Ending
        sf::Music _endingMusic;
};
