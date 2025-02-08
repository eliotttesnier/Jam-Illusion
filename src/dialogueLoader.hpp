/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Dialogue Loader
*/

#pragma once
#include <vector>
#include <string>

class DialogueLoader {
    public:
        static std::vector<std::string> loadFromFile(const std::string& filename);
};
