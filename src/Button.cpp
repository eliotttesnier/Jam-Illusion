/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Button
*/
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Button::Button(const std::string &label, sf::Vector2f position, sf::Vector2f size, std::function<void()> action)
{
    font.loadFromFile("arial.ttf");

    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(100, 100, 250));

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(position.x + 10, position.y + 5);

    onClick = action;
}

void Button::draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (shape.getGlobalBounds() .contains(static_cast<sf::Vector2f>(mousePos))) {
            onClick();
        }
    }
}