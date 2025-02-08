/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Button
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
    public:
        Button(const std::string &label, sf::Vector2f position, sf::Vector2f size, std::function<void()> action);
        void draw(sf::RenderWindow& window);
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    private:
        sf::RectangleShape shape;
        sf::Text text;
        sf::Font font;
        std::function<void()> onClick;
    
};
