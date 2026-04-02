
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
void Game::reset()
{
	window.setView(ui_view);
	in_menu = true;
	play_selected = true;
	score = 0;
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].setIsVisible(true);
	}
	player->getSprite().setPosition(600, 200);

	player->velocity = (0, 0);
	pathfinder->current_node = 0;
	pathfinder->path.clear();

	gameClock.restart();
}
void Game::message(Text& text)
{
	window.clear();
	window.draw(text.string);
	window.display();
	gameClock.restart();

	sf::sleep(sf::seconds(3));
}
bool Game::init()
{
	menu_text.init(200, 0, "Welcome to the Top Down Game.\nCollect all coins in 2 minutes!\nClick to move.\nPlease select an option:", sf::Color::White);
	play_option.init(260, 200, "> Play <", sf::Color::White);
	quit_option.init(720, 200, "Quit", sf::Color::White);
	score_text.init(0, 0, "Score: " + std::to_string(score), sf::Color::Red);
	timer_text.init(900, 10, "n/a", sf::Color::Red);
	win_text.init(500, 360, "You Win!", sf::Color::Green);
	lose_text.init(500, 360, "You Lose!", sf::Color::Red);

	map = std::make_unique<Map>(JsonLoader::LoadMapFromJson("C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Level2.json"));

	player = std::make_unique<GameObject>();

	player->getSprite().setScale(0.2, 0.2);
	player->getSprite().setPosition(600, 360);

	
	player->initialiseSprite(player_texture, "C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Images/kenney_animalpackredux/PNG/Round/bear.png");

	pathfinder = std::make_unique<Pathfinder>();

	std::vector<int> coin_ids = JsonLoader::LoadCoinPositionsFromJson("C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Coin_positions.json");
	for (int i = 0; i < coin_ids.size(); i++)
	{
		std::cout << coin_ids[i] << std::endl;
		Collectible coin;
		coins.push_back(coin);
		coins[i].initialiseSprite(coin_texture, "C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Images/kenney_physicspack/PNG/Other/coinGold.png");
		coins[i].getSprite().setScale(0.7, 0.7);
		coins[i].getSprite().setPosition(map->getTilePosition(coin_ids[i]) - sf::Vector2f(coins[i].getSprite().getGlobalBounds().width / 2, coins[i].getSprite().getGlobalBounds().height / 2));

	}

	sf::Vector2f window_size = static_cast<sf::Vector2f>(window.getSize());

	main_view.reset(sf::FloatRect({ 0,0 }, {window_size.x/main_view_scale_factor, window_size.y/main_view_scale_factor}));
	window.setView(main_view);
	main_view.setCenter(map->GetWidth() * 8, map->GetHeight() * 8);

	ui_view.reset(sf::FloatRect({ 0,0 }, {window_size.x, window_size.y}));

  return true;
}

void Game::update(float dt)
{
	if (in_menu == false)
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
			player->velocity = (0, 0);
			pathfinder->current_node = 0;
			pathfinder->path.clear();
		}
		player->update();
		main_view.setCenter(player->getCentre());

		for (Collectible& coin : coins)
		{
			coin.checkPlayerCollision(*player, score);
		}
		score_text.string.setString("Score: " + std::to_string(score));
		if (score == coins.size())
		{
			reset();
			message(win_text);
		}
		float timeElapsed = gameClock.getElapsedTime().asSeconds();
		timer_text.string.setString("Timer:" + std::to_string(120 - (int)timeElapsed));
		if (timeElapsed > 120.0f)
		{
			reset();
			message(lose_text);
		}
	}
}

void Game::render()
{
	if (in_menu)
	{
		window.setView(ui_view);
		window.draw(menu_text.string);
		window.draw(play_option.string);
		window.draw(quit_option.string);
	}
	else {
		window.setView(main_view);
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
		for (Collectible& coin : coins)
		{
			if (coin.getIsVisible())
			{
				window.draw(coin.getSprite());
			}
		}
		window.setView(ui_view);
		window.draw(score_text.string);
		window.draw(timer_text.string);

		window.setView(main_view);
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

  sf::Vector2f player_pos = player->getSprite().getPosition() + sf::Vector2f(player->getSprite().getGlobalBounds().width / 2, player->getSprite().getGlobalBounds().height / 2);
  if (pathfinder->isTileValid(pathfinder->getTileAtPosition(world_pos, *map).getPosID(), *map))
  {
	  pathfinder->path = pathfinder->findPath(player_pos, world_pos, *map);
	  std::reverse(pathfinder->path.begin(), pathfinder->path.end());
  }
}

void Game::keyPressed(sf::Event event)
{
	if (in_menu == true)
	{
		if ((event.key.code == sf::Keyboard::D) || (event.key.code == sf::Keyboard::A))
		{
			play_selected = !play_selected;
			if (play_selected)
			{
				play_option.string.setString("> Play <");
				quit_option.string.setString("Quit");
			}
			else
			{
				play_option.string.setString("Play");
				quit_option.string.setString("> Quit <");
			}
		}
		if (event.key.code == sf::Keyboard::Enter)
		{
			if (play_selected)
			{
				in_menu = false;
				gameClock.restart();
			}
			else
			{
				window.close();
			}
		}
	}
	else if (in_menu == false)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			reset();
		}
	}
}


