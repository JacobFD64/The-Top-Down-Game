#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Vector.h"

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
	bool collisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2);
	void update();

	Vector velocity;
	Vector position;
	Vector start_position;

private:
	sf::Sprite sprite;
	bool is_visible = true;
};

#endif // TOPDOWN_GAMEOBJECT_H