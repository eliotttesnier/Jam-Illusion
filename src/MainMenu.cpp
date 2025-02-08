#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu() : selectedIndex(0) {
    if (!font.loadFromFile("assets/fonts/font.otf")) {
        throw std::runtime_error("Failed to load font");
    }

    title.setFont(font);
    title.setString("Menu Principal");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    // Center the title text
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(400, 100);  // Assuming window width is 800

    std::vector<std::string> texts = {"Jouer", "Quitter"};
    for (size_t i = 0; i < texts.size(); i++) {
        sf::RectangleShape button(sf::Vector2f(200, 50));
        button.setPosition(300, 200 + i * 70);
        button.setFillColor(sf::Color::White);
        buttons.push_back(button);

        sf::Text text;
        text.setFont(font);
        text.setString(texts[i]);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        // Center text in button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(400, 225 + i * 70);
        options.push_back(text);
    }
}

void MainMenu::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : options.size() - 1;
        } 
        else if (event.key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex < options.size() - 1) ? selectedIndex + 1 : 0;
        } 
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedIndex == 0) {
                std::cout << "Lancement du jeu..." << std::endl;
            } 
            else if (selectedIndex == 1) {
                std::cout << "Fermeture du jeu..." << std::endl;
                exit(0);
            }
        }
    }
}

void MainMenu::draw(sf::RenderWindow& window) {
    if (!font.getInfo().family.empty()) {  // Check if font is loaded
        window.draw(title);
        for (size_t i = 0; i < options.size(); i++) {
            if (i < buttons.size()) {  // Bounds checking
                buttons[i].setFillColor(i == selectedIndex ? sf::Color::Red : sf::Color::White);
                window.draw(buttons[i]);
                window.draw(options[i]);
            }
        }
    }
}
