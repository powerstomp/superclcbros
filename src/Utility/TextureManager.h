#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
class TextureManager {
private:
	std::map<std::string, sf::Texture> textures;

public:
	bool Load(const std::string&);
	bool Has(const std::string&) const;
	const sf::Texture& GetOrLoad(const std::string&);
	const sf::Texture& Get(const std::string&) const;
};

#endif
