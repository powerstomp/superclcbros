#include "TextureManager.h"

#include <SFML/Graphics/Texture.hpp>

bool TextureManager::Load(const std::string& path) {
	sf::Texture texture;
	if (!texture.loadFromFile(path))
		return false;
	textures[path] = texture;
	return true;
}
bool TextureManager::Has(const std::string& path) const {
	return textures.find(path) != textures.end();
}
const sf::Texture& TextureManager::Get(const std::string& path) const {
	return textures.at(path);
}
