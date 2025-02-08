/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
: mWindow(sf::VideoMode(800, 600), "Mon Jeu 2D avec SFML")
, mPlayer()
{
    mWindow.setFramerateLimit(60);
}

void Game::run()
{
    while (mWindow.isOpen())
    {
        processEvents();
        sf::Time deltaTime = mClock.restart();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                mWindow.close();
        }
        mPlayer.handleInput(event);
    }
}

void Game::update(sf::Time deltaTime)
{
    mPlayer.update(deltaTime);
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}
