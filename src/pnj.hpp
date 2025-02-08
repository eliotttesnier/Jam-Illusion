/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** PNJ
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class PNJ {
    public:
        //Constructor
        PNJ(const sf::Vector2f& position, const std::string& dialogueFile);

        //Destructor
        ~PNJ();

        //Getter
        std::string getNextDialogue();

        //Setter
        void set_talking();

        //Method
        void draw(sf::RenderWindow& window);
        bool isColliding(const sf::FloatRect& playerBounds) const;
        void nextDialogue();

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::FloatRect _triggerBox;
        sf::Vector2f pos;
        bool talking;
        std::vector<std::string> _dialogues;
        int _dialogueIndex;
        static sf::Clock _interactionClock;
        static constexpr float _interactionCooldown = 1.0f;
        sf::Font _font;
        sf::Text _dialogueText;
};
