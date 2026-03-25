#pragma once
#include <vector>
#include "Layer.h"

class Map
{
public:
	Map() = default;
    Map(int tileSize, int width, int height);
	void AddLayer(Layer layer);

	std::vector<Layer>& GetLayers() { return layers; };
	int GetTileSize() { return tileSize; };
	int GetWidth() { return mapWidth; };
	int GetHeight() { return mapHeight; };
	std::shared_ptr<sf::Texture>& GetSpriteSheet() { return spritesheet; };

	void SetSpriteSheet(std::string path) { spritesheet->loadFromFile(path); };

private:
	int tileSize;
	int mapWidth;
	int mapHeight;
	std::vector<Layer> layers;
	std::shared_ptr<sf::Texture> spritesheet;

};