#pragma once
#include <vector>
#include <string>
#include "Tile.h"

class Layer
{
public:
	Layer(std::string name, bool collider);

	void AddTile(Tile tile);

	std::string& GetName() { return lname; };
	bool HasCollider() {return hasCollider; };
	std::vector<Tile>& GetTiles() { return tiles; };

private:
	bool hasCollider;
	std::string lname;
	std::vector<Tile> tiles;
};