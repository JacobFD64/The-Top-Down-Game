#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Vector.h"
#include "GameObject.h"

#ifndef TOPDOWN_COLLECTIBLE_H
#define TOPDOWN_COLLECTIBLE_H

class Collectible : public GameObject
{
public:
	void checkPlayerCollision(GameObject player);


private:
	
};

#endif // TOPDOWN_GAMEOBJECT_H