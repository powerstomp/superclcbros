#include "Tilemap.h"

int TileMap::GetHeight() const {
	return tiles.size();
}
int TileMap::GetWidth() const {
	return tiles[0].size();
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.scale(TILE_SCALE, TILE_SCALE);
	states.transform *= getTransform();
	states.texture = &tileset;
	target.draw(vertices, states);
}

TileMap::TileMap(const char* const* const tileData, int width, int height)
	: tileset{ServiceLocator<TextureManager>::Get().GetOrLoad("assets/misc_sprites.png")},
	  tiles(height, std::vector<TileType>(width, TileType::NONE)),
	  vertices(sf::Quads, width * height * 4) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			TileType tileType = static_cast<TileType>(tileData[y][x] - '0');

			SetTile(tileType, x, y);
		}
	}
}

void TileMap::SetTile(TileType type, int x, int y) {
	sf::Vector2f texCoords = atlasPositions[type];

	int index = (x + y * GetWidth()) * 4;
	sf::Vertex* quad = &vertices[index];

	quad[0].position = GetTilePosition(x, y);
	quad[1].position = GetTilePosition(x + 1, y);
	quad[2].position = GetTilePosition(x + 1, y + 1);
	quad[3].position = GetTilePosition(x, y + 1);

	quad[0].texCoords = texCoords;
	quad[1].texCoords = texCoords + GetTilePosition(1, 0);
	quad[2].texCoords = texCoords + GetTilePosition(1, 1);
	quad[3].texCoords = texCoords + GetTilePosition(0, 1);
}
TileType TileMap::GetTile(int x, int y) const {
	return tiles[x][y];
}

sf::Vector2f TileMap::GetTilePosition(int x, int y) {
	return sf::Vector2f(x * TILE_TEXTURE_SIZE, y * TILE_TEXTURE_SIZE);
}
