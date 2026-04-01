#include "Tile.h"

Tile::Tile(int POS_ID,int TILE_ID, int X, int Y, std::shared_ptr<sf::Texture> tex) : pos_id(POS_ID),tile_id(TILE_ID), x(X), y(Y)
{
	texture = std::make_shared<sf::Texture>();
	texture = tex;

	sprite = std::make_unique<sf::Sprite>();
	sprite->setTexture(*texture);
}

bool Tile::isSearched()
{
	return searched;
}