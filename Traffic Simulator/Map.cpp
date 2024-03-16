#include "Map.h"

Map::Map() {
	tile_size = 50;

	sf::Texture texture;
	texture.loadFromFile("textures/grass2.jpg");
	textures.push_back(texture);
	texture.loadFromFile("textures/road_horiz_up.jpg");
	textures.push_back(texture);
	texture.loadFromFile("textures/road_horiz_down.jpg");
	textures.push_back(texture);
	texture.loadFromFile("textures/road_vertic_left.jpg");
	textures.push_back(texture);
	texture.loadFromFile("textures/road_vertic_right.jpg");
	textures.push_back(texture);
	texture.loadFromFile("textures/cross.jpg");
	textures.push_back(texture);

	Map::setRoads();
}

Map::~Map() {

}

void Map::setRoads() {
	const int num_rows = is_road.size();
	const int num_cols = is_road[0].size();

	map_size_x = num_cols * 2;
	map_size_y = num_rows * 2;
	roads.resize(map_size_y, std::vector<int>(map_size_x, 0));

	for (int i = 0; i < num_rows; ++i)
		for (int j = 0; j < num_cols; ++j)
			if (is_road[i][j] == 1) {
				const int row_offset = i * 2;
				const int col_offset = j * 2;
				const int max_cols = num_cols - 1;
				const int max_rows = num_rows - 1;

				if (j == 0) {
					roads[row_offset][col_offset] = 1;
					roads[row_offset + 1][col_offset] = 2;
					roads[row_offset][col_offset + 1] = 6;
					roads[row_offset + 1][col_offset + 1] = 7;
				}
				else if (j == max_cols) {
					roads[row_offset][col_offset + 1] = 1;
					roads[row_offset + 1][col_offset + 1] = 2;
					roads[row_offset][col_offset] = 6;
					roads[row_offset + 1][col_offset] = 7;
				}
				else if (i == 0) {
					roads[row_offset][col_offset] = 3;
					roads[row_offset][col_offset + 1] = 4;
					roads[row_offset + 1][col_offset] = 8;
					roads[row_offset + 1][col_offset + 1] = 9;
				}
				else if (i == max_rows) {
					roads[row_offset + 1][col_offset] = 3;
					roads[row_offset + 1][col_offset + 1] = 4;
					roads[row_offset][col_offset] = 8;
					roads[row_offset][col_offset + 1] = 9;
				}
				else {
					if (is_road[i][j - 1] && is_road[i][j + 1] && is_road[i - 1][j] && is_road[i + 1][j]) {
						roads[row_offset][col_offset] = 5;
						roads[row_offset][col_offset + 1] = 5;
						roads[row_offset + 1][col_offset] = 5;
						roads[row_offset + 1][col_offset + 1] = 5;
					}
					else if (is_road[i][j - 1] && is_road[i][j + 1]) {
						roads[row_offset][col_offset] = 6;
						roads[row_offset + 1][col_offset] = 7;
						roads[row_offset][col_offset + 1] = 6;
						roads[row_offset + 1][col_offset + 1] = 7;
					}
					else if (is_road[i - 1][j] && is_road[i + 1][j]) {
						roads[row_offset][col_offset] = 8;
						roads[row_offset][col_offset + 1] = 9;
						roads[row_offset + 1][col_offset] = 8;
						roads[row_offset + 1][col_offset + 1] = 9;
					}
				}
			}

	Map::setMapSprite();
}

void Map::setMapSprite() {
	map.resize(map_size_x * map_size_y);

	for (int i = 0; i < map_size_y; ++i)
		for (int j = 0; j < map_size_x; ++j) {
			sf::Sprite& tile = map[i * map_size_x + j];
			sf::Texture& texture = Map::select_texture(roads[i][j]);

			texture.setSmooth(true);
			sf::Vector2u textureSize = texture.getSize();
			float scaleX = static_cast<float>(tile_size) / textureSize.x;
			float scaleY = static_cast<float>(tile_size) / textureSize.y;
			tile.setScale(scaleX, scaleY);

			tile.setTexture(texture);
			tile.setPosition(j * tile_size, i * tile_size);
		}

	map_texture.create(tile_size * map_size_x, tile_size * map_size_y);

	for (int i = 0; i < map_size_y; ++i)
		for (int j = 0; j < map_size_x; ++j)
			map_texture.draw(map[i * map_size_x + j]);

	map_texture.display();
	map_sprite.setTexture(map_texture.getTexture());
}

sf::Texture& Map::select_texture(const int choice) {
	switch (choice) {
	case 0:
		return textures[0];
		break;
	case 1:
	case 6:
		return textures[1];
		break;
	case 2:
	case 7:
		return textures[2];
		break;
	case 3:
	case 8:
		return textures[3];
		break;
	case 4:
	case 9:
		return textures[4];
		break;
	case 5:
		return textures[5];
		break;
	default:
		return textures[0];
		break;
	}
}

std::vector<std::vector<int>> Map::getRoads() {
	return roads;
}

void Map::functions(const int change) {

}

bool Map::check() {
	return false;
}