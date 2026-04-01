
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
	map = std::make_unique<Map>(JsonLoader::LoadMapFromJson("C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Level1.json"));

	player = std::make_unique<GameObject>();

	player->getSprite().setScale(0.4, 0.4);
	player->getSprite().setPosition(600, 360);

	
	player->initialiseSprite(player_texture, "C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Images/kenney_animalpackredux/PNG/Round/bear.png");

	pathfinder = std::make_unique<Pathfinder>();

	coin.initialiseSprite(coin_texture, "C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Images/kenney_physicspack/PNG/Other/coinGold.png");

  return true;
}

void Game::update(float dt)
{
	if (pathfinder->current_node < pathfinder->path.size())
	{
		sf::Vector2f target = pathfinder->path[pathfinder->current_node]->GetSprite().getPosition() + sf::Vector2f(map->GetTileSize() / 2, map->GetTileSize() / 2);
		sf::Vector2f direction = target - player->getSprite().getPosition() + sf::Vector2f(player->getSprite().getGlobalBounds().width / 2, player->getSprite().getGlobalBounds().height / 2);
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (player->hasReachedTarget())
		{
          pathfinder->current_node++;
		}
		else
		{
			direction /= distance;
			player->moveTowards(target);
		}
	}
	else
	{
		player->velocity = (0,0);
		pathfinder->current_node = 0;
		pathfinder->path.clear();
	}
	player->update();

	coin.checkPlayerCollision(*player);
}

void Game::render()
{
	for (Layer& layer : map->GetLayers())
	{
		for (Tile& tile : layer.GetTiles())
		{
			tile.GetSprite().setTextureRect(GetRectForTileId(tile.getTileID()));
			if (tile.getTileID() <= 0) continue;

			tile.GetSprite().setPosition(
				(tile.getX() * map->GetTileSize()),
				(tile.getY() * map->GetTileSize())
			);

			window.draw(tile.GetSprite());
		}
	}

	window.draw(player->getSprite());
	if (coin.getIsVisible())
	{
		window.draw(coin.getSprite());
	}
}

sf::IntRect Game::GetRectForTileId(int id)
{
	int tileSize = map->GetTileSize();
	sf::IntRect rect;

	int tilesPerRow = map->GetSpriteSheet()->getSize().x / tileSize;

	int row = id / tilesPerRow ;
	int column = id % tilesPerRow - 1;

	rect.height = tileSize;
	rect.width = tileSize;
	rect.left = column * tileSize;
	rect.top = row * tileSize;

	return rect;
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  sf::Vector2f world_pos = window.mapPixelToCoords(click);
  pathfinder->current_node = 0;
  pathfinder->path.clear();

  sf::Vector2f player_pos = player->getSprite().getPosition() + sf::Vector2f(player->getSprite().getGlobalBounds().width / 2, player->getSprite().getGlobalBounds().height / 2);
  pathfinder->path = pathfinder->findPath(player_pos, world_pos, *map);
  std::reverse(pathfinder->path.begin(), pathfinder->path.end());

  

}

void Game::keyPressed(sf::Event event)
{

}


