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
    // Initialize menus first
    _mainMenu = MainMenu();
    _pauseMenu = PauseMenu();
    _currentMenu = &_mainMenu;
    _currentScene = GameState::MAIN_MENU;

    // Window and view setup
    _clock.restart();
    _deltaTime = 0.0f;
    _window.create(sf::VideoMode(1920, 1080), "Jamy-llusion", sf::Style::Titlebar);
    _window.setFramerateLimit(60);
    _view.setSize(sf::Vector2f(1920, 1080));
    _view.zoom(0.25f);

    // Initialize rooms and narrations first
    _currentRoom = 0;
    initializeRooms();
    loadNarrations();

    // Initialize player after rooms
    _player = Player();
    _view.setCenter(_player.getCenter());
    _player.setGame(this);
    setCurrentRoom(0);

    // Interactions HUD setup
    _canInteract = false;
    if (!_interactFont.loadFromFile("assets/fonts/font.otf")) {
        throw std::runtime_error("Failed to load interaction font");
    }
    _interactText.setFont(_interactFont);
    _interactText.setCharacterSize(50);
    _interactText.setScale(0.25, 0.25);
    _interactText.setFillColor(sf::Color(255, 255, 255, 0));
    _interactText.setString("Appuyez sur E (Clavier) ou B (Manette) pour interagir...");
}

Game::~Game()
{
    // Clean up rooms
    for (auto* room : _rooms) {
        delete room;
    }
    _rooms.clear();
}

void Game::initializeRooms() {
    // Clear any existing rooms first
    for (auto* room : _rooms) {
        delete room;
    }
    _rooms.clear();

    try {
        std::vector<IRoom*> newRooms;

        // Create rooms one by one with error handling
        auto addRoom = [&newRooms](IRoom* room) {
            if (!room) {
                throw std::runtime_error("Failed to create room");
            }
            newRooms.push_back(room);
        };

        addRoom(new Exterior(1));
        addRoom(new FirstRoom(2));
        addRoom(new SecondRoom(3));
        addRoom(new FirstRoom(4));
        addRoom(new ThirdRoom(5));
        addRoom(new SecondRoom(6));
        addRoom(new FourthRoom(7));
        addRoom(new FirstRoom(8));
        addRoom(new FirstRoom(9));
        addRoom(new FirstRoom(10));
        addRoom(new FirstRoom(11));
        addRoom(new Final());

        // If all rooms were created successfully, assign to _rooms
        _rooms = newRooms;
        
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialize rooms: " << e.what() << std::endl;
        // Clean up any rooms that were created before the error
        for (auto* room : _rooms) {
            delete room;
        }
        _rooms.clear();
        throw; // Re-throw to handle at higher level
    }
}

void Game::loadNarrations()
{
    for (size_t i = 0; i < _rooms.size(); i++) {
        std::string path = "assets/sounds/wav/narration" + std::to_string(i + 1) + ".wav";
        auto music = std::make_unique<sf::Music>();
        if (!music->openFromFile(path)) {
            std::cerr << "Warning: Could not load narration " << path << std::endl;
            continue;
        }
        _narrations.push_back(std::move(music));
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
    _canInteract = false;
    for (auto &Object : _rooms[_currentRoom]->getObjects()) {
        if (Object.isColliding(_player.getSprite().getGlobalBounds()))
            _canInteract = true;
    }
    for (auto &pnj : _rooms[_currentRoom]->getPNJs()) {
        if (pnj->isColliding(_player.getSprite().getGlobalBounds()))
            _canInteract = true;
    }
    if (_narrations[_currentRoom].get()->getStatus() == sf::Music::Playing)
        _interactText.setString("Vous ne pouvez pas interagir pendant que vous entendez des voix...");
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
    if (currentRoom < 0 || currentRoom >= static_cast<int>(_rooms.size())) {
        std::cerr << "Invalid room index: " << currentRoom << std::endl;
        return;
    }
    _currentRoom = currentRoom;
    _canInteract = false;
    _interactText.setFillColor(sf::Color(255, 255, 255, 0));
    _player.setPosition(_rooms[_currentRoom]->getSpawnPoint());
    
    if (_currentRoom < static_cast<int>(_narrations.size()) && _narrations[_currentRoom]) {
        _narrations[_currentRoom]->play();
    }
}

std::vector<IRoom *> Game::getRooms() const
{
    return _rooms;
}

sf::Music::Status Game::getNarrationStatus() const
{
    if (_currentRoom < static_cast<int>(_narrations.size()) && _narrations[_currentRoom]) {
        return _narrations[_currentRoom]->getStatus();
    }
    return sf::Music::Stopped;
}
