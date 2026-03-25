#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile(int POS_ID, int TILE_ID, int X, int Y, std::shared_ptr<sf::Texture> tex);

	int getPosID() const { return pos_id; }
	int getTileID() const { return tile_id; }
	int getX() const { return x; }
	int getY() const { return y; }
    sf::Sprite& GetSprite() { return *sprite; };

private:
	std::unique_ptr<sf::Sprite> sprite;

	std::shared_ptr<sf::Texture> texture;
	int pos_id;
	int tile_id;
	int x;
	int y;

};