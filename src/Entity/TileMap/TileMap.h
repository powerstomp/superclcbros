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
	GROUND
};

struct Tileset {
	const sf::Texture& texture;
	int tileSize;
	int n, m;
	int margin, spacing;
};

class TileMap : public sf::Drawable, public sf::Transformable {
private:
	const Tileset tileset;
	std::vector<std::vector<TileType>> tiles;

	sf::VertexArray vertices;

	int GetHeight() const;
	int GetWidth() const;

	sf::Vector2f GetUnscaledTilePosition(int x, int y);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	TileMap(
		const std::vector<std::vector<int>>& tileData, int width, int height,
		const Tileset& tileset
	);

	void SetTile(int id, int x, int y);
	TileType GetTile(int x, int y) const;

	static sf::Vector2f GetTilePosition(int x, int y);
	static sf::FloatRect GetTileBoundingBox(int x, int y);
};

#endif
