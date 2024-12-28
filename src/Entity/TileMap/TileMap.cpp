#include "TileMap.h"

#include <iostream>

int TileMap::GetHeight() const {
	return tiles.size();
}
int TileMap::GetWidth() const {
	return tiles[0].size();
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	auto textureScale = static_cast<float>(TILE_SIZE) / tileset.tileSize;
	states.transform.scale(textureScale, textureScale);
	states.transform *= getTransform();
	states.texture = &tileset.texture;
	target.draw(vertices, states);
}

TileMap::TileMap(
	const std::vector<std::vector<int>>& tileData, int width, int height,
	const Tileset& tileset
)
	: tileset(tileset),
	  tiles(height, std::vector<TileType>(width, TileType::NONE)),
	  vertices(sf::Quads, width * height * 4) {
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			SetTile(tileData[y][x], x, y);
}

void TileMap::SetTile(int id, int x, int y) {
	if (id == -1)
		return;

	int index = (x + y * GetWidth()) * 4;
	sf::Vertex* quad = &vertices[index];

	quad[0].position = GetUnscaledTilePosition(x, y);
	quad[1].position = GetUnscaledTilePosition(x + 1, y);
	quad[2].position = GetUnscaledTilePosition(x + 1, y + 1);
	quad[3].position = GetUnscaledTilePosition(x, y + 1);

	int sheetRow = id / tileset.m;
	int sheetColumn = id % tileset.m;
	sf::Vector2f texCoords(
		tileset.margin + sheetColumn * (tileset.tileSize + tileset.spacing),
		tileset.margin + sheetRow * (tileset.tileSize + tileset.spacing)
	);

	quad[0].texCoords = texCoords;
	quad[1].texCoords = texCoords + GetUnscaledTilePosition(1, 0);
	quad[2].texCoords = texCoords + GetUnscaledTilePosition(1, 1);
	quad[3].texCoords = texCoords + GetUnscaledTilePosition(0, 1);

	tiles[y][x] = TileType::GROUND;
}
TileType TileMap::GetTile(int x, int y) const {
	if (x <= 0)
		return TileType::GROUND;
	if (x < 0 || y < 0 || x >= GetWidth() || y >= GetHeight())
		return TileType::NONE;
	return tiles[y][x];
}

sf::Vector2f TileMap::GetUnscaledTilePosition(int x, int y) {
	return sf::Vector2f(x * tileset.tileSize, y * tileset.tileSize);
}

sf::Vector2f TileMap::GetTilePosition(int x, int y) {
	return sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
}
sf::FloatRect TileMap::GetTileBoundingBox(int x, int y) {
	return sf::FloatRect(GetTilePosition(x, y), GetTilePosition(1, 1));
}
