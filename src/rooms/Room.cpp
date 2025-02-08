/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Room
*/

#include "Room.hpp"
#include <random>
#include <filesystem>
#include <iostream>

Room::Room()
{
    // Initialize all member pointers to nullptr
    _spawnPoint = sf::Vector2f(0, 0);
}

Room::~Room()
{
    // Clean up PNJs
    for (auto* pnj : _pnjs) {
        delete pnj;
    }
    _pnjs.clear();
}

// Methods
void Room::draw(sf::RenderWindow &window)
{
    _sprite.setTexture(_texture);
    window.draw(_sprite);
    for(auto &object: _objects) {
        object.update();
        object.draw(window);
    }
    for (auto &pnj : _pnjs) {
        pnj->draw(window);
    }
}

bool Room::loadTexture(const std::string& path) {
    if (!_texture.loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return false;
    }
    _sprite.setTexture(_texture);
    return true;
}

bool Room::loadCollisionMap(const std::string& path) {
    if (!_collisions.loadFromFile(path)) {
        std::cerr << "Failed to load collision map: " << path << std::endl;
        return false;
    }
    return true;
}

bool Room::validatePaths(const std::string& texturePath, const std::string& collisionPath) const {
    std::filesystem::path texture(texturePath);
    std::filesystem::path collision(collisionPath);
    
    if (!std::filesystem::exists(texture)) {
        std::cerr << "Texture file does not exist: " << texturePath << std::endl;
        return false;
    }
    
    if (!std::filesystem::exists(collision)) {
        std::cerr << "Collision map file does not exist: " << collisionPath << std::endl;
        return false;
    }
    
    return true;
}

// Getters
sf::Image Room::getCollisions() const
{
    return _collisions;
}

std::vector<Object> Room::getObjects() const
{
    return _objects;
}

sf::Vector2f Room::getSpawnPoint() const
{
    return _spawnPoint;
}

std::vector<PNJ *> Room::getPNJs() const
{
    return _pnjs;
}

sf::Vector2u Room::getMapSize() const
{
    return _texture.getSize();
}

bool Room::isValidDialogPosition(const sf::Vector2f& position) const
{
    sf::FloatRect pnjBounds(position.x, position.y, 15, 23); // Taille du PNJ
    sf::FloatRect interactionArea(position.x - 25, position.y - 25, 65, 73); // Zone élargie pour l'interaction

    // Vérifie les collisions aux quatre coins de la zone d'interaction
    std::vector<sf::Vector2i> points = {
        sf::Vector2i(interactionArea.left, interactionArea.top),
        sf::Vector2i(interactionArea.left + interactionArea.width, interactionArea.top),
        sf::Vector2i(interactionArea.left, interactionArea.top + interactionArea.height),
        sf::Vector2i(interactionArea.left + interactionArea.width, interactionArea.top + interactionArea.height)
    };

    for (const auto& point : points) {
        if (point.x >= 0 && point.x < (int)_collisions.getSize().x &&
            point.y >= 0 && point.y < (int)_collisions.getSize().y) {
            if (_collisions.getPixel(point.x, point.y) == sf::Color::Red) {
                return false;
            }
        }
    }
    return true;
}

sf::Vector2f Room::generateRandomPosition() const
{
    sf::Vector2f position;
    do {
        std::random_device rd;
        std::mt19937 gen(rd());

        sf::Vector2u size = getMapSize();
        std::uniform_int_distribution<> disX(20, size.x - 20);
        std::uniform_int_distribution<> disY(20, size.y - 20);

        position = sf::Vector2f(disX(gen), disY(gen));
    } while (!isValidDialogPosition(position));

    return position;
}
