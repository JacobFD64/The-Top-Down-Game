
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
#include "Pathfinder.h"
#include "Text.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void reset();
  void message(Text& text);
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  sf::IntRect GetRectForTileId(int id);

  std::vector<Collectible>  coins;

  sf::Texture coin_texture;

  Text menu_text;
  Text play_option;
  Text quit_option;
  Text score_text;
  Text timer_text;
  Text win_text;
  Text lose_text;

  bool play_selected;
  bool in_menu = true;
  bool is_pathfinding = false;
  bool pathing = false;

  int score = 0;

 private:
  sf::RenderWindow& window;
  
  std::unique_ptr <Map> map;

  std::unique_ptr <GameObject> player;

  std::unique_ptr <Pathfinder> pathfinder;

  sf::Texture player_texture;

  sf::View main_view;

  sf::View ui_view;
  
  sf::Clock gameClock;
  
  float main_view_scale_factor = 1.4;

};

#endif // PLATFORMER_GAME_H
