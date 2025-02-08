#include "FontManager.hpp"
#include <iostream>

FontManager& FontManager::getInstance() {
    static FontManager instance;
    return instance;
}

sf::Font* FontManager::getFont(const std::string& path) {
    auto it = _fonts.find(path);
    if (it != _fonts.end()) {
        return it->second.get();
    }

    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(path)) {
        std::cerr << "Failed to load font: " << path << std::endl;
        return nullptr;
    }

    sf::Font* fontPtr = font.get();
    _fonts[path] = std::move(font);
    return fontPtr;
}
