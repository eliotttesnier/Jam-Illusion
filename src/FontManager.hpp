#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>

class FontManager {
public:
    static FontManager& getInstance();
    sf::Font* getFont(const std::string& path);

private:
    FontManager() = default;
    ~FontManager() = default;
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    std::unordered_map<std::string, std::unique_ptr<sf::Font>> _fonts;
};
