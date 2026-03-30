
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Tile.h"
#include "Map.h"
#include "GameObject.h"
#include "JsonLoader.h"
#include "Vector.h"
#include "Collectible.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

  sf::IntRect GetRectForTileId(int id);

  Collectible coin;

  sf::Texture coin_texture;

 private:
  sf::RenderWindow& window;
  
  std::unique_ptr <Map> map;

  std::unique_ptr <GameObject> player;

  sf::Texture player_texture;

};

#endif // PLATFORMER_GAME_H
