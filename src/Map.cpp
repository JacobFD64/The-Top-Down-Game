#include "Map.h"

Map::Map(int tileSize, int width, int height) : tileSize(tileSize), mapWidth(width), mapHeight(height)
{
	spritesheet = std::make_shared<sf::Texture> ();
}

void Map::AddLayer(Layer layer)
{
	layers.push_back(std::move(layer));
}

Tile& Map::getTileAtPosition(sf::Vector2f& pos)
{
	int tile_col = pos.x / GetTileSize();
	int tile_row = pos.y / GetTileSize();

	int tile_id = tile_col + (tile_row * GetWidth());

	Tile& tile = GetLayers()[0].GetTiles()[tile_id];

	return tile;
}
sf::Vector2f Map::getTilePosition(int id)
{
	return sf::Vector2f(id % GetWidth() * GetTileSize(), id / GetHeight() * GetTileSize() ) + sf::Vector2f(GetTileSize() / 2, GetTileSize() / 2);
}