/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Player
*/

#include "Player.hpp"
// #include "ResourceManager.hpp"

Player::Player()
: mSpeed(200.f)
{
    // ResourceManager::loadTexture("player", "assets/images/player.png");
    // mTexture = ResourceManager::getTexture("player");

    mSprite.setTexture(mTexture);
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    mSprite.setPosition(400.f, 300.f);
}

void Player::update(sf::Time deltaTime)
{
    float dt = deltaTime.asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        mSprite.move(0, -mSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        mSprite.move(0, mSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        mSprite.move(-mSpeed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        mSprite.move(mSpeed * dt, 0);
}

void Player::handleInput(const sf::Event& event)
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
