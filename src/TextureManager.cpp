#include "TextureManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <stdexcept>

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
const sf::Texture& TextureManager::GetOrLoad(const std::string& path) {
	auto it = textures.find(path);
	if (it != textures.end())
		return it->second;
	if (!Load(path))
		throw std::runtime_error("Couldn't load texture " + path);
	return Get(path);
}
const sf::Texture& TextureManager::Get(const std::string& path) const {
	return textures.at(path);
}
