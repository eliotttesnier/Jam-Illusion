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
    _currentTrack = MENU;
}

Music::~Music()
{
    _music.stop();
}

void Music::play(Type type)
{
    if (_currentTrack == type && isPlaying()) {
        return;
    }

    std::string path = (type == MENU) ? _menuMusicPath : _gameMusicPath;

    if (!_music.openFromFile(path)) {
        std::cerr << "Erreur : Impossible de charger la musique " << path << std::endl;
        return;
    }

    _currentTrack = type;
    _music.setLoop(true);
    _music.setVolume(25);
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

Music::Type Music::getCurrentTrack() const
{
    return _currentTrack;
}