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

    // Menus
    _currentScene = SCENE::GAME;
    _mainMenu = MainMenu();

    //PNJ
    _pnjs.push_back(PNJ(sf::Vector2f(50, 50), "dialogues/room0.txt"));

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
    if (_currentScene == SCENE::MAIN_MENU) {
        _mainMenu.update();
        _view.setSize(sf::Vector2f(1920, 1080));
        _view.setCenter(960, 540);
        _window.setView(_view);
        return;
    }

    for (auto& pnj : _pnjs) {
        if (pnj.isColliding(_player.getSprite().getGlobalBounds())) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                pnj.set_talking();
                pnj.nextDialogue();
            }
        }
    }

    _player.update(_deltaTime, *_rooms[_currentRoom]);
    _view.setCenter(_player.getCenter());
    _window.setView(_view);

    // Interactions HUD
    for (auto &Object : _rooms[_currentRoom]->getObjects()) {
        if (Object.isColliding(_player.getSprite().getGlobalBounds())) {
            _canInteract = true;
        } else {
            _canInteract = false;
        }
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
    _rooms[_currentRoom]->draw(_window);
    for (auto& pnj : _pnjs) {
        pnj.draw(_window);
    }
  _player.draw(_window);
    _interactText.setFont(_interactFont);
    _window.draw(_interactText);
    _window.display();
}

int Game::getCurrentRoom() const
{
    return _currentRoom;
}

void Game::setCurrentRoom(int currentRoom)
{
    _currentRoom = currentRoom;
}

std::vector<IRoom *> Game::getRooms() const
{
    return _rooms;
}
