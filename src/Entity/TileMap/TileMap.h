#ifndef _TILEMAP_H
#define _TILEMAP_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>

#include "../../Definitions.h"

enum class TileType {
	NONE,
	GROUND,
	QUESTION
};

static constexpr int TILE_TEXTURE_SIZE = 16;
static constexpr auto TILE_SCALE = static_cast<float>(TILE_SIZE) / TILE_TEXTURE_SIZE;

static std::map<TileType, sf::Vector2f> atlasPositions = {
	{TileType::NONE, sf::Vector2f(0, 0)},
	{TileType::GROUND, sf::Vector2f(373, 124)},
	{TileType::QUESTION, sf::Vector2f(372, 160)}
};

class TileMap : public sf::Drawable, public sf::Transformable {
private:
	const sf::Texture& tileset;
	std::vector<std::vector<TileType>> tiles;

	sf::VertexArray vertices;

	int GetHeight() const;
	int GetWidth() const;

	static sf::Vector2f GetTileTexturePosition(int x, int y);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	TileMap(const char* const* const tileData, int width, int height);

	void SetTile(TileType type, int x, int y);
	TileType GetTile(int x, int y) const;

	static sf::Vector2f GetTilePosition(int x, int y);
	static sf::FloatRect GetTileBoundingBox(int x, int y);
};

#endif
