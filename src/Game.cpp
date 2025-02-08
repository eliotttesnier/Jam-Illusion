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
    _window.create(sf::VideoMode(1920, 1080), "Jamy-llusion", sf::Style::Fullscreen | sf::Style::Titlebar);
    _window.setFramerateLimit(60);
    _player = Player();
    _view.setCenter(_player.getCenter());
    _view.setSize(sf::Vector2f(1920, 1080));
    _view.zoom(0.25f);
    // _music.play(Music::MENU);

    // Rooms
    _currentRoom = 0;
    _rooms.push_back(new Exterior(1));
    _rooms.push_back(new FirstRoom(2));
    _rooms.push_back(new SecondRoom(3));
    _rooms.push_back(new FirstRoom(4));
    _rooms.push_back(new ThirdRoom(5));
    _rooms.push_back(new SecondRoom(6));
    _rooms.push_back(new FourthRoom(7));
    _rooms.push_back(new FirstRoom(8));
    _rooms.push_back(new FirstRoom(9));
    _rooms.push_back(new FirstRoom(10));
    _rooms.push_back(new FirstRoom(11));
    _rooms.push_back(new Final());
    for (int i = 1; i < (int)_rooms.size() + 1; i++) {
        std::string path = "assets/sounds/wav/narration" + std::to_string(i) + ".wav";
        auto music = std::make_unique<sf::Music>();
        music->openFromFile(path);
        _narrations.push_back(std::move(music));
    }

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
    setCurrentRoom(0);
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
            if (getNarrationStatus() == sf::Music::Playing)
                _narrations[_currentRoom].get()->pause();
            _mainMenu.handleEvent(event);
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0)) {
                std::cout << "Démarrage du jeu..." << std::endl;
                _currentScene = GameState::GAME;
            }
        }
        else if (_currentScene == GameState::GAME) {
            if (getNarrationStatus() == sf::Music::Paused)
                _narrations[_currentRoom].get()->play();
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 11)) {
                std::cout << "Pause activée..." << std::endl;
                _currentScene = GameState::PAUSE;
                _currentMenu = &_pauseMenu;
            }
        }
        else if (_currentScene == GameState::PAUSE) {
            if (getNarrationStatus() == sf::Music::Playing)
                _narrations[_currentRoom].get()->pause();
            _pauseMenu.handleEvent(event);
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 11)) {
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
        if (!_music.isPlaying() || _music.getCurrentTrack() != Music::MENU) {
            // _music.stop();
            // _music.play(Music::MENU);
        }
        _mainMenu.update();
        _view.setSize(sf::Vector2f(1920, 1080));
        _view.setCenter(960, 540);
        _window.setView(_view);
        return;
    } else {
        if (!_music.isPlaying() || _music.getCurrentTrack() != Music::GAME) {
            // _music.stop();
            // _music.play(Music::GAME);
        }
        _view.setSize(sf::Vector2f(1920, 1080));
        _view.zoom(0.25f);
    }

    _player.update(_deltaTime, *_rooms[_currentRoom]);
    _view.setCenter(_player.getCenter());
    _window.setView(_view);

    // Interactions HUD
    bool blocked = false;
    _canInteract = false;
    for (auto &Object : _rooms[_currentRoom]->getObjects()) {
        if (Object->isColliding(_player.getSprite().getGlobalBounds())) {
            _canInteract = true;
            if (Object->getType() == Object::Type::DOOR && Object->isLocked()) {
                blocked = true;
            }
        }
    }
    for (auto &pnj : _rooms[_currentRoom]->getPNJs()) {
        if (pnj->isColliding(_player.getSprite().getGlobalBounds()))
            _canInteract = true;
    }
    if (_narrations[_currentRoom].get()->getStatus() == sf::Music::Playing)
        _interactText.setString("Vous ne pouvez pas interagir pendant que vous entendez des voix...");
    else if (blocked)
        _interactText.setString("La porte est fermee...");
    else
        _interactText.setString("Appuyez sur E (Clavier) ou B (Manette) pour interagir...");
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
    _interactText.setFillColor(sf::Color(255, 255, 255, 0));
    _player.setPosition(_rooms[_currentRoom]->getSpawnPoint());
    _narrations[_currentRoom].get()->play();
}

std::vector<IRoom *> Game::getRooms() const
{
    return _rooms;
}

sf::Music::Status Game::getNarrationStatus() const
{
    return _narrations[_currentRoom].get()->getStatus();
}
