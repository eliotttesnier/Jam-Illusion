/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    _clock.restart();
    _deltaTime = 0.0f;
    _window.create(sf::VideoMode(1920, 1080), "Jam-Illusion", sf::Style::Fullscreen | sf::Style::Titlebar);
    _window.setFramerateLimit(60);
    _player = Player();
    _view.setCenter(_player.getCenter());
    _view.setSize(sf::Vector2f(1920, 1080));
    _view.zoom(0.25f);

    // Rooms
    _currentRoom = 0;
    _rooms.push_back(Room(1));
    _objects[0] = std::vector<Object>();
    _objects[0].push_back(Object(sf::FloatRect(133, 31, 21, 10), "Door"));

    // Menus
    _currentScene = GameState::MAIN_MENU;
    _currentMenu = &_mainMenu;
    _mainMenu = MainMenu();
}

Game::~Game()
{
}

void Game::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        
        if (_currentScene == GameState::MAIN_MENU) {
            _mainMenu.handleEvent(event);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                std::cout << "Démarrage du jeu..." << std::endl;
                _currentScene = GameState::GAME;
            }
        } 
        else if (_currentScene == GameState::GAME) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                std::cout << "Pause activée..." << std::endl;
                _currentScene = GameState::PAUSE;
                _currentMenu = &_pauseMenu;
            }
        }
        else if (_currentScene == GameState::PAUSE) {
            _pauseMenu.handleEvent(event);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                std::cout << "Reprise du jeu..." << std::endl;
                _currentScene = GameState::GAME;
                _currentMenu = &_mainMenu;
            }
        }
    }
}

void Game::run()
{
    while (_window.isOpen()) {
        processEvents();
        _deltaTime = _clock.restart().asSeconds();
        update();
        draw();
    }
}

void Game::update()
{
    if (_currentScene == GameState::MAIN_MENU) {
        _mainMenu.update();
        _view.setSize(sf::Vector2f(1920, 1080));
        _view.setCenter(960, 540);
        _window.setView(_view);
        return;
    }
    _player.update(_deltaTime, _rooms[_currentRoom].getCollisions(), _objects[_currentRoom]);
    _view.setCenter(_player.getCenter());
    _window.setView(_view);
}

void Game::draw()
{
    _window.clear();
    if (_currentScene == GameState::MAIN_MENU) {
        _rooms[_currentRoom].draw(_window);
        _window.display();
        return;
    } else if (_currentScene == GameState::PAUSE) {
        _rooms[_currentRoom].draw(_window);
        _window.display();
    } else {
        _rooms[_currentRoom].draw(_window);
        _player.draw(_window);
        _window.display();
    }
}
