#include "Collectible.h"

void Collectible::checkPlayerCollision(GameObject player, int& score)
{
	if (getIsVisible())
	{
		if (collisionCheck(getSprite(), player.getSprite()))
		{
			setIsVisible(false);
			score++;
		}
	}
}