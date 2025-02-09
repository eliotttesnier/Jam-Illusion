/*
** EPITECH PROJECT, 2025
** Jam-Illusion
** File description:
** Dialogue Loader
*/

#include "dialogueLoader.hpp"
#include <fstream>
#include <iostream>

std::vector<std::wstring> DialogueLoader::loadFromFile(const std::string& filename)
{
    std::vector<std::wstring> dialogues;
    std::wifstream file(filename);

    if (!file.is_open()) {
        std::wcerr << L"Erreur : Impossible d'ouvrir le fichier " << filename.c_str() << std::endl;
        return dialogues;
    }

    file.imbue(std::locale(""));
    std::wstring line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            dialogues.push_back(line);
        }
    }

    file.close();
    return dialogues;
}
