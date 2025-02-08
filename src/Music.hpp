/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Music
*/

#pragma once

#include <SFML/Audio.hpp>
#include <string>

class Music {
    public:
        enum Type {
            MENU,
            GAME
        };

        Music();
        ~Music();

        void play(Type type);
        void stop();
        void setVolume(float volume);
        bool isPlaying() const;

    private:
        sf::Music _music;
        std::string _menuMusicPath;
        std::string _gameMusicPath;
};
