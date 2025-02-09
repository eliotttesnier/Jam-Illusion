/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Player
*/

#include "Player.hpp"
#include "Game.hpp"
#include <cmath>

// Constructor
Player::Player()
{
    _speed = 150.0f;
    _currentFrame = 0;
    _position = sf::Vector2f(352 / 2, 288 / 2);
    _direction = sf::Vector2f(0.0f, 0.0f);
    _currentDirection = Direction::DOWN;

    // Graphics
    _animationClock.restart();
    _textures[Direction::UP] = std::vector<sf::Texture>(6);
    _textures[Direction::DOWN] = std::vector<sf::Texture>(6);
    _textures[Direction::LEFT] = std::vector<sf::Texture>(6);
    _textures[Direction::RIGHT] = std::vector<sf::Texture>(6);
    _textures[Direction::IDLE] = std::vector<sf::Texture>(6);

    for (int i = 1; i < 7; i++) {
        _textures[Direction::UP][i - 1].loadFromFile("assets/player/up/" + std::to_string(i) + ".png");
        _textures[Direction::DOWN][i - 1].loadFromFile("assets/player/down/" + std::to_string(i) + ".png");
        _textures[Direction::LEFT][i - 1].loadFromFile("assets/player/left/" + std::to_string(i) + ".png");
        _textures[Direction::RIGHT][i - 1].loadFromFile("assets/player/right/" + std::to_string(i) + ".png");
        _textures[Direction::IDLE][i - 1].loadFromFile("assets/player/idle/" + std::to_string(i) + ".png");
    }
}

Player::~Player()
{
}

// Methods
void Player::update(float deltaTime, IRoom &room)
{
    handleInput(room.getObjects());
    move(deltaTime);
    CheckCollisions(room.getCollisions(), deltaTime);
    animate(deltaTime);
}

void Player::handleInput(std::vector<Object *> objects)
{
    static sf::Clock interactionClock;
    float joystickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float joystickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    _direction = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || joystickY < -25) {
        _direction.y -= 1.0f;
        _currentDirection = Direction::UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || joystickY > 25) {
        _direction.y += 1.0f;
        _currentDirection = Direction::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickX < -25) {
        _direction.x -= 1.0f;
        _currentDirection = Direction::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || joystickX > 25) {
        _direction.x += 1.0f;
        _currentDirection = Direction::RIGHT;
    }
    if (_direction.x == 0 && _direction.y == 0) {
        _currentDirection = Direction::IDLE;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::isButtonPressed(0, 10)) {
        _game->getRooms()[_game->getCurrentRoom()]->getObjects()[0]->unlock();
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, 0)) && interactionClock.getElapsedTime().asSeconds() > 0.5f) {
        for (const auto &object : objects) {
            if (object->isColliding(_sprite.getGlobalBounds())) {
                if (object->getType() == Object::Type::DOOR) {
                    if (_game->getNarrationStatus() == sf::Music::Playing)
                        break;
                    if (object->isLocked())
                        break;
                    _game->setCurrentRoom(object->getRedirectTo());
                    interactionClock.restart();
                    break;
                }
                if (object->getType() == Object::Type::LIBRARY) {
                    if (_game->getNarrationStatus() == sf::Music::Playing)
                        break;
                    if (object->isScreaming())
                        break;
                    object->scream();
                    _game->setScreaming(true);
                    interactionClock.restart();
                    if (_game->getCurrentRoom() == 2)
                        _game->getRooms()[2]->getObjects()[0]->unlock();
                    if (_game->getCurrentRoom() == 5)
                        _game->getRooms()[5]->getObjects()[0]->unlock();
                    break;
                }
                if (object->getType() == Object::Type::BARREL) {
                    if (_game->getNarrationStatus() == sf::Music::Playing)
                        break;
                    object->barrelSound();
                    interactionClock.restart();
                    if (_game->getCurrentRoom() == 4)
                        _game->getRooms()[4]->getObjects()[0]->unlock();
                    break;
                }
                if (object->getType() == Object::Type::BED) {
                    if (_game->getNarrationStatus() == sf::Music::Playing)
                        break;
                    _game->playEnding();
                    interactionClock.restart();
                    break;
                }
            }
        }
        for (auto &pnj : _game->getRooms()[_game->getCurrentRoom()]->getPNJs()) {
            if (pnj->isColliding(_sprite.getGlobalBounds())) {
                if (_game->getNarrationStatus() == sf::Music::Playing)
                        break;
                // Events
                if (_game->getCurrentRoom() == 1)
                    _game->getRooms()[1]->getObjects()[0]->unlock();
                if (_game->getCurrentRoom() == 3)
                    _game->getRooms()[3]->getObjects()[0]->unlock();
                if (_game->getCurrentRoom() == 7)
                    _game->getRooms()[7]->getObjects()[0]->unlock();
                if (_game->getCurrentRoom() == 8)
                    _game->getRooms()[8]->getObjects()[0]->unlock();
                if (_game->getCurrentRoom() == 9)
                    _game->getRooms()[9]->getObjects()[0]->unlock();
                if (_game->getCurrentRoom() == 10)
                    _game->getRooms()[10]->getObjects()[0]->unlock();

                pnj->set_talking();
                pnj->nextDialogue();
                interactionClock.restart();
                break;
            }
        }
    }
    for (auto &object : objects) {
        if (object->getType() == Object::Type::LIBRARY && !object->isScreaming())
            _game->setScreaming(false);
    }
}

void Player::move(float deltaTime)
{
    if (_game->getScreaming())
        return;

    if (_direction.x != 0 && _direction.y != 0) {
        _direction /= std::sqrt(2.0f);
    }
    _position += _direction * _speed * deltaTime;
    _sprite.setPosition(_position);
}

void Player::setPosition(const sf::Vector2f &position)
{
    _position = position;
    _sprite.setPosition(_position);
}

sf::Vector2f Player::getPosition() const
{
    return _position;
}

sf::Vector2f Player::getCenter() const
{
    return sf::Vector2f(_position.x + _sprite.getGlobalBounds().width / 2, _position.y + _sprite.getGlobalBounds().height / 2);
}

void Player::setSpeed(float speed)
{
    _speed = speed;
}

float Player::getSpeed() const
{
    return _speed;
}

void Player::CheckCollisions(const sf::Image &collisions, float deltaTime)
{
    sf::Color collisionColor = sf::Color::Red;
    sf::FloatRect playerBounds = _sprite.getGlobalBounds();

    std::vector<sf::Vector2i> pointsToCheck = {
        sf::Vector2i(playerBounds.left, playerBounds.top + playerBounds.height / 1.5),
        sf::Vector2i(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height / 1.5),
        sf::Vector2i(playerBounds.left, playerBounds.top + playerBounds.height),
        sf::Vector2i(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height)
    };

    for (const auto &point : pointsToCheck) {
        if (point.x >= 0 && point.x < (int)collisions.getSize().x && point.y >= 0 && point.y < (int)collisions.getSize().y) {
            if (collisions.getPixel(point.x, point.y) == collisionColor) {
                _position -= _direction * _speed * deltaTime;
                _sprite.setPosition(_position);
                return;
            }
        }
    }
}

void Player::animate(float deltaTime)
{
    if (_animationClock.getElapsedTime().asSeconds() > 0.1f) {
        _currentFrame = (_currentFrame + 1) % 4;
        _animationClock.restart();
    }
}

void Player::draw(sf::RenderWindow &window)
{
    if (_game->getScreaming())
        return;

    _sprite.setTexture(_textures[_currentDirection][_currentFrame]);
    window.draw(_sprite);
}

const sf::Sprite &Player::getSprite() const
{
    return _sprite;
}

void Player::setGame(Game *game)
{
    _game = game;
    _position = _game->getRooms()[_game->getCurrentRoom()]->getSpawnPoint();
}
