/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** MainMenu
*/

#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu() : selectedIndex(0) {
    font.loadFromFile("arial.ttf");

    title.setFont(font);
    title.setString("Menu Principal");
    title.setCharacterSize(50);
    title.setPosition(300, 100);

    std::vector<std::string> texts = {"Jouer", "Quitter"};
    for (size_t i = 0; i < texts.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(texts[i]);
        text.setCharacterSize(30);
        text.setPosition(350, 200 + i * 50);
        options.push_back(text);
    }
}

void MainMenu::handleEvent() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : options.size() - 1;
        std::cout << "Option sélectionnée : " << options[selectedIndex].getString().toAnsiString() << std::endl;
        sf::sleep(sf::milliseconds(150)); // To prevent rapid key press
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        selectedIndex = (selectedIndex < options.size() - 1) ? selectedIndex + 1 : 0;
        std::cout << "Option sélectionnée : " << options[selectedIndex].getString().toAnsiString() << std::endl;
        sf::sleep(sf::milliseconds(150)); // To prevent rapid key press
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if (selectedIndex == 0) {
            std::cout << "Lancement du jeu..." << std::endl;
        }
        else if (selectedIndex == 1) {
            std::cout << "Fermeture du jeu..." << std::endl;
            exit(0);
        }
        sf::sleep(sf::milliseconds(150)); // To prevent rapid key press
    }
}

void MainMenu::render(sf::RenderWindow& window) {
    window.draw(title);
    for (size_t i = 0; i < options.size(); i++) {
        options[i].setFillColor(i == selectedIndex ? sf::Color::Red : sf::Color::White);
        window.draw(options[i]);
    }
}

void MainMenu::update() {
    handleEvent();
}
