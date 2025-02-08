/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow &window) : window(window), isInMainMenu(true) {
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Erreur de chargement de la police!" << std::endl;
    }

    initializeButtons();
    initializeText();
}

void Menu::initializeButtons() {
    playButton.setSize(sf::Vector2f(200, 50));
    playButton.setPosition(300, 150);
    playButton.setFillColor(sf::Color::Green);

    settingsButton.setSize(sf::Vector2f(200, 50));
    settingsButton.setPosition(300, 250);
    settingsButton.setFillColor(sf::Color::Yellow);

    quitButton.setSize(sf::Vector2f(200, 50));
    quitButton.setPosition(300, 350);
    quitButton.setFillColor(sf::Color::Red);

    resumeButton.setSize(sf::Vector2f(200, 50));
    resumeButton.setPosition(300, 150);
    resumeButton.setFillColor(sf::Color::Green);

    pauseSettingsButton.setSize(sf::Vector2f(200, 50));
    pauseSettingsButton.setPosition(300, 250);
    pauseSettingsButton.setFillColor(sf::Color::Yellow);

    pauseQuitButton.setSize(sf::Vector2f(200, 50));
    pauseQuitButton.setPosition(300, 350);
    pauseQuitButton.setFillColor(sf::Color::Red);
}

void Menu::initializeText() {
    playText.setFont(font);
    playText.setString("Jouer");
    playText.setCharacterSize(24);
    playText.setFillColor(sf::Color::Black);
    playText.setPosition(340, 160);

    settingsText.setFont(font);
    settingsText.setString("Paramètres");
    settingsText.setCharacterSize(24);
    settingsText.setFillColor(sf::Color::Black);
    settingsText.setPosition(320, 260);

    quitText.setFont(font);
    quitText.setString("Quitter");
    quitText.setCharacterSize(24);
    quitText.setFillColor(sf::Color::Black);
    quitText.setPosition(340, 360);

    resumeText.setFont(font);
    resumeText.setString("Reprendre");
    resumeText.setCharacterSize(24);
    resumeText.setFillColor(sf::Color::Black);
    resumeText.setPosition(340, 160);

    pauseSettingsText.setFont(font);
    pauseSettingsText.setString("Paramètres");
    pauseSettingsText.setCharacterSize(24);
    pauseSettingsText.setFillColor(sf::Color::Black);
    pauseSettingsText.setPosition(320, 260);

    pauseQuitText.setFont(font);
    pauseQuitText.setString("Quitter");
    pauseQuitText.setCharacterSize(24);
    pauseQuitText.setFillColor(sf::Color::Black);
    pauseQuitText.setPosition(340, 360);
}

void Menu::drawButtons() {
    if (isInMainMenu) {
        window.draw(playButton);
        window.draw(settingsButton);
        window.draw(quitButton);
    } else {
        window.draw(resumeButton);
        window.draw(pauseSettingsButton);
        window.draw(pauseQuitButton);
    }
}

void Menu::drawText() {
    if (isInMainMenu) {
        window.draw(playText);
        window.draw(settingsText);
        window.draw(quitText);
    } else {
        window.draw(resumeText);
        window.draw(pauseSettingsText);
        window.draw(pauseQuitText);
    }
}

void Menu::handleMainMenuInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Lancer le jeu..." << std::endl;
        } else if (settingsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Paramètres..." << std::endl;
        } else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            window.close();
        }
    }
}

void Menu::handlePauseMenuInput(bool &isPaused) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isPaused = false;
        } else if (pauseSettingsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Paramètres..." << std::endl;
        } else if (pauseQuitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            window.close();
        }
    }
}

void Menu::handleInput(bool &isPaused) {
    if (isInMainMenu) {
        handleMainMenuInput();
    } else {
        handlePauseMenuInput(isPaused);
    }
}

void Menu::draw() {
    window.clear();
    drawButtons();
    drawText();
    window.display();
}

void Menu::showMainMenu() {
    isInMainMenu = true;
}

void Menu::showPauseMenu() {
    isInMainMenu = false;
}
