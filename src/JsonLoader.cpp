#include "JsonLoader.h"

nlohmann::json JsonLoader::loadJson(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		std::cout << "couldnt open map file" << std::endl;
	}

	nlohmann::json j;
	file >> j;
	return j;
}

Map JsonLoader::LoadMapFromJson(std::string path)
{
	try {
		nlohmann::json j = loadJson(path);

		int tileSize = j.at("tileheight").get<int>();
		int mapWidth = j.at("height").get<int>();
		int mapHeight = j.at("width").get<int>();

		Map map(tileSize, mapWidth, mapHeight);
		map.SetSpriteSheet("C:/Users/JacobFD64/Source/Repos/The-Top-Down-Game/Data/Tiny Top Down 32x32.png");

		for (auto& jsonLayer : j.at("layers"))
		{
			std::string name = jsonLayer.at("name").get<std::string>();
			bool collider = jsonLayer.at("collider").get<bool>();

			Layer layer(name, collider);

			auto& data = jsonLayer.at("data");

			for (size_t i = 0; i < data.size(); i++)
			{
				int tile_id = data[i].get<int>();
				int pos_id = i;

				int x = i % map.GetWidth();
				int y = i / map.GetHeight();

				bool iscollidable = collider;



				layer.AddTile(Tile(pos_id,tile_id, x, y,iscollidable, map.GetSpriteSheet()));
			}

			map.AddLayer(std::move(layer));
		}
		return map;
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cout << "Parse error: " << e.what() << std::endl;
	}


}
std::vector<int> JsonLoader::LoadCoinPositionsFromJson(std::string path)
{
	nlohmann::json j = loadJson(path);

	std::vector<int> coin_positions;

	for (auto& coin : j.at("Coins"))
	{
		coin_positions.push_back(coin.get<int>());
	}

	return coin_positions;
}