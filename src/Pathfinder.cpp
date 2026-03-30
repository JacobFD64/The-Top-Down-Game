#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

void Pathfinder::initNodes(Map& map)
{

}

void Pathfinder::findPath(sf::Vector2f& start_pos, sf::Vector2f& target_pos, Map& map)
{
	// make a list of all the tiles to search and have been searched
	std::vector<Node> tile_ids_to_search;
	std::vector<Node> tile_ids_searched;
	
	// get the id of the start and target tile
	int start_tile_id = getTileIdAtPosition(start_pos, map);
	int target_tile_id = getTileIdAtPosition(target_pos, map);

	// add the start tile to the list to be searched
	tile_ids_to_search.push_back(start_tile_id);

	for (int i = 0; i < tile_ids_to_search.size(); i++)
	{
		if (i == target_tile_id)
		{
			// end and loop back over parent tiles
		}
        // add the tile to the list of searched tiles
		tile_ids_searched.push_back(tile_ids_to_search[i]);

		// get the tile ids of the next tiles to check
		int right_tile_id = i + 1;
		int left_tile_id = i - 1;
		int top_tile_id = i - map.GetWidth();
		int bottom_tile_id = i + map.GetWidth();

		// add them to the list to be searched if not searched already
		tile_ids_to_search.push_back(right_tile_id);
		tile_ids_to_search.push_back(left_tile_id);
		tile_ids_to_search.push_back(top_tile_id);
		tile_ids_to_search.push_back(bottom_tile_id);
        
	}



}

int Pathfinder::getTileIdAtPosition(sf::Vector2f& pos, Map& map)
{
	int tile_col = pos.x / map.GetTileSize();
	int tile_row = pos.y / map.GetTileSize();

	int tile_id = tile_col + (tile_row * map.GetWidth());

	return tile_id;
}