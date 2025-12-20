#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace Minesweeper {
    class TextureManager {
    public:
        static TextureManager& getInstance();
        
        // Texture management
        bool loadTexture(const std::string& name, const std::string& filename);
        const sf::Texture& getTexture(const std::string& name) const;
        
        // Cleanup
        void clear();
        
    private:
        TextureManager() = default;
        ~TextureManager() = default;
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;
        
        std::map<std::string, sf::Texture> textures_;
    };
}
