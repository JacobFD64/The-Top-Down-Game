#include "Layer.h"

Layer::Layer(std::string name, bool collider) : lname(name), hasCollider(collider) {}

void Layer::AddTile(Tile tile)
{
	tiles.push_back(std::move(tile));
}