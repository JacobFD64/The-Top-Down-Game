
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
	map = std::make_unique<Map>(JsonLoader::LoadMapFromJson("C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Templatelvl.json"));

	player = std::make_unique<GameObject>();

	player->getSprite().setScale(0.6, 0.6);
	player->getSprite().setPosition(540, 360);

	
	player->initialiseSprite(player_texture, "C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Images/kenney_animalpackredux/PNG/Round/bear.png");

  return true;
}

void Game::update(float dt)
{
	player->velocity.x = target_position.x;
	player->velocity.y = target_position.y;

	player->update();
}

void Game::render()
{
	for (Layer& layer : map->GetLayers())
	{
		for (Tile& tile : layer.GetTiles())
		{
			tile.GetSprite().setTextureRect(GetRectForTileId(tile.getTileID()));
			if (tile.getTileID() <= 0) continue;

			float scale_y_multiplier = 1.8;
			float scale_x_multiplier = 1.8;

			tile.GetSprite().setScale(
				scale_x_multiplier,
				scale_y_multiplier
			);
			
			tile.GetSprite().setPosition(
			((tile.getX() * map->GetTileSize()) * scale_x_multiplier) + (540 - (map->GetWidth() * (map->GetTileSize() * scale_x_multiplier) / 2)),
			((tile.getY() * map->GetTileSize()) * scale_y_multiplier) + (360 - (map->GetHeight() * (map->GetTileSize() * scale_y_multiplier) / 2))
			);

			window.draw(tile.GetSprite());
		}
	}

	window.draw(player->getSprite());
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

  target_position.x = click.x - player->getSprite().getPosition().x;
  target_position.y = click.y - player->getSprite().getPosition().y;

  target_position.normalise();

  std::cout << target_position.x << " " << target_position.y << std::endl;


}

void Game::keyPressed(sf::Event event)
{

}


