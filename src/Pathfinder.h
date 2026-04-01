#include <SFML/System.hpp>

#include "Map.h"
#include "Tile.h"
#include <queue>


#ifndef TOPDOWN_PATHFINDER_H
#define TOPDOWN_PATHFINDER_H

class Pathfinder
{
public:

	Pathfinder();
	~Pathfinder();
	std::vector<Tile*> findPath(sf::Vector2f& start_pos, sf::Vector2f& target_pos, Map& map);
	Tile& getTileAtPosition(sf::Vector2f& pos, Map& map);

	bool isTileValid(int tile_id, Map& map);
	void addTileToQueue(int tile_id, std::queue<Tile*>& tile_queue, Map& map, Tile& parent_tile);
	void reset(Map& map);

	int current_node = 0;

	
	std::vector<Tile*> path;

private:


	std::unique_ptr<Map> map;

};

#endif // TOPDOWN_PATHFINDER_H