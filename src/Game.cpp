/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Game
*/

#include "Game.hpp"
#include "Exterior.hpp"
#include "FirstRoom.hpp"
#include "SecondRoom.hpp"
#include "ThirdRoom.hpp"
#include "FourthRoom.hpp"
#include "Final.hpp"

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
    _rooms.push_back(new Exterior());
    _rooms.push_back(new FirstRoom());
    _rooms.push_back(new SecondRoom());
    _rooms.push_back(new ThirdRoom());
    _rooms.push_back(new FourthRoom());
    _rooms.push_back(new Final());

    // Menus
    _currentScene = GameState::MAIN_MENU;
    _currentMenu = &_mainMenu;
    _mainMenu = MainMenu();

    // Interactions HUD
    _canInteract = false;
    _interactFont.loadFromFile("assets/fonts/font.otf");
    _interactText.setFont(_interactFont);
    _interactText.setCharacterSize(50);
    _interactText.setScale(0.25, 0.25);
    _interactText.setFillColor(sf::Color(255, 255, 255, 0));
    _interactText.setString("Appuyez sur E (Clavier) ou B (Manette) pour interagir...");

    _player.setGame(this);
}

Game::~Game()
{
    for (auto &room : _rooms) {
        delete room;
    }
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

    _player.update(_deltaTime, *_rooms[_currentRoom]);
    _view.setCenter(_player.getCenter());
    _window.setView(_view);

    // Interactions HUD
    _canInteract = false;
    for (auto &Object : _rooms[_currentRoom]->getObjects()) {
        if (Object.isColliding(_player.getSprite().getGlobalBounds()))
            _canInteract = true;
    }
    for (auto &pnj : _rooms[_currentRoom]->getPNJs()) {
        if (pnj->isColliding(_player.getSprite().getGlobalBounds()))
            _canInteract = true;
    }
    _interactText.setPosition(_view.getCenter().x - _view.getSize().x / 2 + 2, _view.getCenter().y - _view.getSize().y / 2 - 2);

    static sf::Clock timer;
    sf::Uint8 opacity = _interactText.getFillColor().a;

    if (timer.getElapsedTime().asSeconds() >= 0.01f) {
        if (_canInteract) {
            if (opacity >= 250)
                opacity = 255;
            else
                opacity += 5;
        } else {
            if (opacity <= 5)
                opacity = 0;
            else
                opacity -= 5;
        }
        _interactText.setFillColor(sf::Color(255, 255, 255, opacity));
        timer.restart();
    }
}

void Game::draw()
{
    _window.clear();
    if (_currentScene == GameState::MAIN_MENU) {
        _rooms[_currentRoom]->draw(_window);
        _window.display();
        return;
    } else if (_currentScene == GameState::PAUSE) {
        _rooms[_currentRoom]->draw(_window);
        _window.display();
    } else {
        _rooms[_currentRoom]->draw(_window);
        _player.draw(_window);
        _interactText.setFont(_interactFont);
        _window.draw(_interactText);
        _window.display();
    }
}

int Game::getCurrentRoom() const
{
    return _currentRoom;
}

void Game::setCurrentRoom(int currentRoom)
{
    _currentRoom = currentRoom;
    _canInteract = false;
}

std::vector<IRoom *> Game::getRooms() const
{
    return _rooms;
}
