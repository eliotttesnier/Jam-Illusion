/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** MainMenu
*/

#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu() : Menu() {
    font.loadFromFile("assets/fonts/font.otf");

    title.setFont(font);
    title.setString("Menu Principal");
    title.setCharacterSize(50);
    title.setPosition(300, 100);

    std::vector<std::string> texts = {"Jouer", "Paramètres", "Quitter"};
    for (size_t i = 0; i < texts.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(texts[i]);
        text.setCharacterSize(30);
        text.setPosition(350, 200 + i * 50);
        options.push_back(text);
    }
}
