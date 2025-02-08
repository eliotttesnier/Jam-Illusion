/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** PNJ
*/

#include "pnj.hpp"
#include "dialogueLoader.hpp"
#include <iostream>

sf::Clock PNJ::_interactionClock;

PNJ::PNJ(const sf::Vector2f& position, const std::string& dialogueFile)
{
    pos = position;
    for (int i = 1; i < 7; i++) {
        sf::Texture texture;
        texture.loadFromFile("assets/player/idle/" + std::to_string(i) + ".png");
        _textures.push_back(texture);
    }
    _sprite.setTexture(_textures[0]);
    _sprite.setPosition(position);

    _triggerBox = sf::FloatRect(position.x, position.y, _sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);

    _dialogues = DialogueLoader::loadFromFile(dialogueFile);
    _dialogueIndex = 0;

    if (_dialogues.empty()) {
        _dialogues.push_back("...");
    }

    if (_font.loadFromFile("assets/fonts/font.otf")) {
        _dialogueText.setFont(_font);
    }
    _dialogueText.setCharacterSize(30);
    const sf::Vector2f scale{0.33f, 0.33f};
    _dialogueText.setScale(scale);
    _dialogueText.setFillColor(sf::Color::White);
    _dialogueText.setString(_dialogues[_dialogueIndex]);
    _dialogueText.setPosition(position.x - (_dialogueText.getGlobalBounds().width / 2), position.y - _dialogueText.getGlobalBounds().height - 10);
    _talking = false;
    _talkingTimer.restart();
    _currentFrame = 0;
    _animationClock.restart();
}

PNJ::~PNJ()
{

}

std::string PNJ::getNextDialogue()
{
    std::string message = _dialogues[_dialogueIndex];
    _dialogueIndex = (_dialogueIndex + 1) % _dialogues.size();
    return message;
}

void PNJ::set_talking()
{
    _talking = true;
    _talkingTimer.restart();
}

void PNJ::draw(sf::RenderWindow& window)
{
    if (_talking && _talkingTimer.getElapsedTime().asSeconds() > 2) {
        _talking = false;
    }
    if (_animationClock.getElapsedTime().asSeconds() > 0.1f) {
        _currentFrame = (_currentFrame + 1) % 6;
        _animationClock.restart();
    }
    _sprite.setTexture(_textures[_currentFrame]);
    window.draw(_sprite);
    if (_talking) {
        if (!_dialogues.empty()) {
            _dialogueText.setFont(_font);
            _dialogueText.setPosition(pos.x - (_dialogueText.getGlobalBounds().width / 2) + 7.5, pos.y - _dialogueText.getGlobalBounds().height - 10);
            window.draw(_dialogueText);
        }
    }
}

bool PNJ::isColliding(const sf::FloatRect& playerBounds) const
{
    sf::FloatRect bottomHalf(playerBounds.left, playerBounds.top + playerBounds.height / 1.5, playerBounds.width, playerBounds.height / 1.5);
    sf::FloatRect biggerTriggerBox(_triggerBox.left - 10, _triggerBox.top - 10, _triggerBox.width + 20, _triggerBox.height + 20);

    return biggerTriggerBox.intersects(bottomHalf);
}

void PNJ::nextDialogue()
{
    if (_dialogues.empty()) {
        return;
    }

    if (_interactionClock.getElapsedTime().asSeconds() < _interactionCooldown) {
        return;
    }

    _interactionClock.restart();
    _dialogueIndex = (_dialogueIndex + 1) % _dialogues.size();
    _dialogueText.setString(_dialogues[_dialogueIndex]);
}
