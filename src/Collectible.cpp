#include "Collectible.h"

void Collectible::checkPlayerCollision(GameObject player)
{
	if (getIsVisible())
	{
		if (collisionCheck(getSprite(), player.getSprite()))
		{
			setIsVisible(false);
		}
	}
}