/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Menu
*/

#pragma once

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow &window);
    void showMainMenu();
    void showPauseMenu();
    void handleInput(bool &isPaused);
    void draw();

private:
    sf::RenderWindow &window;
    sf::Font font;
    sf::Text playText;
    sf::Text settingsText;
    sf::Text quitText;
    sf::Text resumeText;
    sf::Text pauseSettingsText;
    sf::Text pauseQuitText;

    sf::RectangleShape playButton;
    sf::RectangleShape settingsButton;
    sf::RectangleShape quitButton;
    sf::RectangleShape resumeButton;
    sf::RectangleShape pauseSettingsButton;
    sf::RectangleShape pauseQuitButton;

    bool isInMainMenu;
    void initializeButtons();
    void initializeText();
    void drawButtons();
    void drawText();
    void handleMainMenuInput();
    void handlePauseMenuInput(bool &isPaused);
};
