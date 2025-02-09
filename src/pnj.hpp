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
        std::wstring getNextDialogue();

        //Setter
        void set_talking();

        //Method
        void draw(sf::RenderWindow& window);
        bool isColliding(const sf::FloatRect& playerBounds) const;
        void nextDialogue();

    private:
        sf::Sprite _sprite;
        sf::FloatRect _triggerBox;
        sf::Vector2f pos;
        bool _talking;
        std::vector<std::wstring> _dialogues;
        int _dialogueIndex;
        static sf::Clock _interactionClock;
        static constexpr float _interactionCooldown = 0.5f;
        sf::Font _font;
        sf::Text _dialogueText;
        sf::Clock _talkingTimer;

        // Animation
        std::vector<sf::Texture> _textures;
        int _currentFrame;
        sf::Clock _animationClock;
};
