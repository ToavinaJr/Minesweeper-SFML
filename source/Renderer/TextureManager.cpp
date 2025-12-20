#include "../../include/Renderer/TextureManager.hpp"
#include <iostream>

namespace Minesweeper {
    TextureManager& TextureManager::getInstance() {
        static TextureManager instance;
        return instance;
    }

    bool TextureManager::loadTexture(const std::string& name, const std::string& filename) {
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            textures_[name] = texture;
            return true;
        }
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }

    const sf::Texture& TextureManager::getTexture(const std::string& name) const {
        auto it = textures_.find(name);
        if (it != textures_.end()) {
            return it->second;
        }
        static sf::Texture emptyTexture;
        return emptyTexture;
    }

    void TextureManager::clear() {
        textures_.clear();
    }
}
