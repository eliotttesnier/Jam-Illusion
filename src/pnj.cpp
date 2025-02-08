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
    _texture.loadFromFile("assets/player/idle/1.png");
    _sprite.setTexture(_texture);
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
    talking = false;
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
    talking = true;
}

void PNJ::draw(sf::RenderWindow& window)
{
    _sprite.setTexture(_texture);
    window.draw(_sprite);
    if (talking) {
        if (!_dialogues.empty()) {
            _dialogueText.setFont(_font);
            _dialogueText.setPosition(pos.x - (_dialogueText.getGlobalBounds().width / 2) + 7.5, pos.y - _dialogueText.getGlobalBounds().height - 10);
            window.draw(_dialogueText);
        }
    }
}

bool PNJ::isColliding(const sf::FloatRect& playerBounds) const
{
    return _triggerBox.intersects(playerBounds);
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

