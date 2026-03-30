#include <SFML/System.hpp>

#include "Map.h"
#include "Tile.h"
#include "Node.h"


#ifndef TOPDOWN_PATHFINDER_H
#define TOPDOWN_PATHFINDER_H

class Pathfinder
{
public:

	Pathfinder();
	~Pathfinder();

    void initNodes(Map& map);
	void findPath(sf::Vector2f& start_pos, sf::Vector2f& target_pos, Map& map);
	int getTileIdAtPosition(sf::Vector2f& pos, Map& map);


private:


	std::unique_ptr<Map> map;

};

#endif // TOPDOWN_PATHFINDER_H