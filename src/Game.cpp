
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

	player->getSprite().setScale(0.6, 0.6);
	player->getSprite().setPosition(540, 360);

	
	player->initialiseSprite(player_texture, "C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Images/kenney_animalpackredux/PNG/Round/bear.png");

	coin.initialiseSprite(coin_texture, "C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Images/kenney_physicspack/PNG/Other/coinGold.png");

  return true;
}

void Game::update(float dt)
{
	if (player->hasReachedTarget())
	{
		player->velocity = Vector(0, 0);
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

			/*float scale_y_multiplier = 1.8;
			float scale_x_multiplier = 1.8;*/

			/*tile.GetSprite().setScale(
				scale_x_multiplier,
				scale_y_multiplier
			);*/
			
			/*tile.GetSprite().setPosition(
			((tile.getX() * map->GetTileSize()) * scale_x_multiplier) + (540 - (map->GetWidth() * (map->GetTileSize() * scale_x_multiplier) / 2)),
			((tile.getY() * map->GetTileSize()) * scale_y_multiplier) + (360 - (map->GetHeight() * (map->GetTileSize() * scale_y_multiplier) / 2))
			);*/

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

  int clicked_tile_col = world_pos.x / map->GetTileSize();
  int clicked_tile_row = world_pos.y / map->GetTileSize();

  int clicked_tile_id = clicked_tile_col + (clicked_tile_row * map->GetWidth());

  std::cout << clicked_tile_col << " " << clicked_tile_row << std::endl;
  std::cout << clicked_tile_id << std::endl;

  map->GetLayers()[0].GetTiles()[clicked_tile_id].GetSprite().setColor(sf::Color::Red);
  map->GetLayers()[0].GetTiles()[clicked_tile_id + 1].GetSprite().setColor(sf::Color::Red);
  map->GetLayers()[0].GetTiles()[clicked_tile_id - 1].GetSprite().setColor(sf::Color::Red);
  map->GetLayers()[0].GetTiles()[clicked_tile_id - map->GetWidth()].GetSprite().setColor(sf::Color::Red);
  map->GetLayers()[0].GetTiles()[clicked_tile_id + map->GetWidth()].GetSprite().setColor(sf::Color::Red);

  player->moveTowards(click);

}

void Game::keyPressed(sf::Event event)
{

}


