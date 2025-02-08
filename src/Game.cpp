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
    _window.create(sf::VideoMode(1920, 1080), "Jam-Illusion");
    _window.setFramerateLimit(60);
    _player = Player();
    _view.setCenter(_player.getCenter());
    _view.setSize(sf::Vector2f(1920, 1080));
    _view.zoom(0.25f);

    // Rooms
    _currentRoom = 0;
    _rooms.push_back(Room(1));
}

Game::~Game()
{
}

void Game::run()
{
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _window.close();
                break;
            }
        }

        _deltaTime = _clock.restart().asSeconds();

        update();
        draw();
    }
}

void Game::update()
{
    _player.update(_deltaTime, _rooms[_currentRoom].getCollisions());
    _view.setCenter(_player.getCenter());
    _window.setView(_view);
}

void Game::draw()
{
    _window.clear();
    _rooms[_currentRoom].draw(_window);
    _player.draw(_window);
    _window.display();
}
