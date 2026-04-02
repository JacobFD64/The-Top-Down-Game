#include "Pathfinder.h"
#include <queue>
#include <iostream>

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

std::vector<Tile*> Pathfinder::findPath(sf::Vector2f& start_pos, sf::Vector2f& target_pos, Map& map)
{
	reset(map);
	// make a list of all the tiles to search and have been searched
	std::queue<Tile*> tiles_to_search;
	
	// get the id of the start and target tile
	Tile& start_tile = getTileAtPosition(start_pos, map);
	Tile& target_tile = getTileAtPosition(target_pos, map);

	// add the start tile to the list to be searched
	tiles_to_search.push(&start_tile);
	while (!tiles_to_search.empty())
	{
		//Get id of front tile in queue then remove it
		Tile* current = tiles_to_search.front();
		tiles_to_search.pop();
		// add the id to the searched list
		current->setSearched(true);

		 //Check if the id is the target tile
		if (current->getPosID() == target_tile.getPosID())
		{
			std::vector<Tile*> path;

			while (current->getPosID() != start_tile.getPosID())
			{
				path.push_back(current);
				current = &map.GetLayers()[0].GetTiles()[current->getParentTileID()];
			}
			return path;
		}
		// add ajacent tiles to queue
		addTileToQueue(current->getPosID() + 1, tiles_to_search, map,*current);
		addTileToQueue(current->getPosID() - 1, tiles_to_search, map, *current);
		addTileToQueue(current->getPosID() - map.GetWidth(), tiles_to_search, map, *current);
		addTileToQueue(current->getPosID() + map.GetWidth(), tiles_to_search, map, *current);
	}

}

void Pathfinder::addTileToQueue(int tile_id, std::queue<Tile*>& tile_queue, Map& map, Tile& parent_tile)
{
	Tile& tile = map.GetLayers()[0].GetTiles()[tile_id];

	if (isTileValid(tile_id, map) && !tile.isSearched())
	{
		tile_queue.push(&tile);
		tile.setParentTileID(parent_tile.getPosID());
	}
	tile.setSearched(true);
}

bool Pathfinder::isTileValid(int tile_id, Map& map)
{
	bool valid = true;

	for (Layer& layer : map.GetLayers())
	{
		if (layer.GetTiles()[tile_id].getTileID() == 11)
		{
			valid = false;
		}
		else
		{
			valid = true;
		}
	}
	return valid;
}

Tile& Pathfinder::getTileAtPosition(sf::Vector2f& pos, Map& map)
{
	int tile_col = pos.x / map.GetTileSize();
	int tile_row = pos.y / map.GetTileSize();

	int tile_id = tile_col + (tile_row * map.GetWidth());

	Tile& tile = map.GetLayers()[0].GetTiles()[tile_id];

	return tile;
}
void Pathfinder::reset(Map& map)
{
	for (Tile& tile : map.GetLayers()[0].GetTiles())
	{
		tile.setSearched(false);
		tile.GetSprite().setColor(sf::Color::White);
	}
	current_node = 0;
	path.clear();
}