/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Dialogue Loader
*/

#include "dialogueLoader.hpp"
#include <fstream>
#include <iostream>

std::vector<std::string> DialogueLoader::loadFromFile(const std::string& filename)
{
    std::vector<std::string> dialogues;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        return dialogues;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            dialogues.push_back(line);
        }
    }

    file.close();
    return dialogues;
}
