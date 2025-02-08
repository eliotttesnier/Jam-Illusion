/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Music
*/

#include "Music.hpp"
#include <iostream>

Music::Music()
{
    _menuMusicPath = "assets/music/menu.wav";
    _gameMusicPath = "assets/music/game.wav";
}

Music::~Music()
{
    _music.stop();
}

void Music::play(Type type)
{
    std::string path = (type == MENU) ? _menuMusicPath : _gameMusicPath;

    if (!_music.openFromFile(path)) {
        std::cerr << "Erreur : Impossible de charger la musique " << path << std::endl;
        return;
    }

    _music.setLoop(true);
    _music.play();
}

void Music::stop()
{
    _music.stop();
}

void Music::setVolume(float volume)
{
    _music.setVolume(volume);
}

bool Music::isPlaying() const
{
    return _music.getStatus() == sf::Music::Playing;
}
