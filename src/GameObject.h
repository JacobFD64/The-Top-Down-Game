#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Vector.h"
#include "Map.h"
#include "Pathfinder.h"

#ifndef TOPDOWN_GAMEOBJECT_H
#define TOPDOWN_GAMEOBJECT_H

class GameObject
{
public:
	GameObject();
	~GameObject();

	bool initialiseSprite(sf::Texture& texture, std::string filename);
	sf::Sprite& getSprite();
	void setIsVisible(bool visibility);
	bool getIsVisible();
	int getSpeed() { return speed; };
	sf::Vector2f getCentre();
	bool collisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2);
	bool collisionCheckTiles(sf::Sprite& sprite,Map& map, Pathfinder& pathfinder);
	void moveTowards(sf::Vector2f& target);
    bool hasReachedTarget();
	void update();

	Vector velocity;
	Vector position;
	Vector direction;

	sf::Vector2f target_position;

private:
	sf::Sprite sprite;
	bool is_visible = true;

	int speed = 4;
};

#endif // TOPDOWN_GAMEOBJECT_H