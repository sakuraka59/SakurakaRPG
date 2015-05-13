#include "RandomDungeonRoom.h"
#include "../../Random.h"
#include "randomRoadType.h"

/*
class Random;
enum class randomRoadType;
*/

RandomDungeonRoom::RandomDungeonRoom(int room_width_max, int room_height_max, int road_size,
	int dungeon_map_x, int dungeon_map_y, int map_frame_size, Random* rand_obj)
{
	this->_road_size = road_size;
	this->_rand_obj = rand_obj;

	this->_dungeon_map_x = dungeon_map_x;
	this->_dungeon_map_y = dungeon_map_y;

//	this->_map_data = new int[dungeon_map_x, dungeon_map_y];

	for (int x = 0; x < dungeon_map_x; x++) {
		for (int y = 0; y < dungeon_map_y; y++) {
			this->_map_data[x][y] = 1;
		}
	}


	// 各ブロックごとに部屋を作成する --------------------------------------
	// 部屋のサイズを決定する
	int room_width = rand_obj->getRandNum(room_width_max) + (road_size + 2);
	int room_height = rand_obj->getRandNum(room_height_max) + (road_size + 2);

	// 10%の確率で部屋のサイズが通路になる可能性が出来る
	if (rand_obj->getRandNum(100) < 10) {
		room_width = rand_obj->getRandNum(room_width_max) + (road_size);
		room_height = rand_obj->getRandNum(room_height_max) + (road_size);
	}


	this->_room_width = room_width;
	this->_room_height = room_height;
	// へやの左上の座標を指定
	int rand_x_point = rand_obj->getRandNum(((dungeon_map_x - (map_frame_size * 2)) - room_width) + 1) + map_frame_size;
	int rand_y_point = rand_obj->getRandNum(((dungeon_map_y - (map_frame_size * 2)) - room_height) + 1) + map_frame_size;


	this->_room_x = rand_x_point;
	this->_room_y = rand_y_point;

	// 部屋を作成
	for (int map_base_x = 0; map_base_x < room_width; map_base_x++) {
		for (int map_base_y = 0; map_base_y < room_height; map_base_y++) {

			int map_x = map_base_x;
			int map_y = map_base_y;
			this->_map_data[map_x + rand_x_point][map_y + rand_y_point] = 2;

		}
	}
	// */
}
void RandomDungeonRoom::setDungeonRoad(int room_block_x, int room_block_y, int dungeon_block_x, int dungeon_block_y) {

	// 左側へ伸ばす
	if (room_block_x > 0) {
		// 場所をランダム設定
		int load_position = this->_rand_obj->getRandNum(this->_room_height - this->_road_size);
		this->_load_position_left = load_position;

		// 通路を延ばす
		for (int x = 0; x < this->_room_x; x++) {
			for (int y = 0; y < this->_road_size; y++) {
				this->_map_data[x][y + load_position + this->_room_y] = 3;
			}
		}
	}

	// 右側へ伸ばす
	if (room_block_x < dungeon_block_x - 1) {
		// 場所をランダム設定
		int load_position = this->_rand_obj->getRandNum(this->_room_height - this->_road_size);
		this->_load_position_right = load_position;
		// 通路を延ばす
		for (int x = this->_dungeon_map_x - 1; x >= this->_room_x + this->_room_width; x--) {
			for (int y = 0; y < this->_road_size; y++) {
				this->_map_data[x][y + load_position + this->_room_y] = 3;
			}
		}
	}

	// 上側へ伸ばす
	if (room_block_y > 0) {
		// 場所をランダム設定
		int load_position = this->_rand_obj->getRandNum(this->_room_width - this->_road_size);
		this->_load_position_top = load_position;
		// 通路を延ばす
		for (int x = 0; x < this->_road_size; x++) {
			for (int y = 0; y < this->_room_y; y++) {
				this->_map_data[x + load_position + this->_room_x][y] = 3;
			}
		}
	}

	// 下側へ伸ばす
	if (room_block_y < dungeon_block_y - 1) {
		// 場所をランダム設定
		int load_position = this->_rand_obj->getRandNum(this->_room_width - this->_road_size);
		this->_load_position_bottom = load_position;
		// 通路を延ばす
		for (int x = 0; x < this->_road_size; x++) {

			for (int y = this->_dungeon_map_y - 1; y >= this->_room_y + this->_room_height; y--) {
				this->_map_data[x + load_position + this->_room_x][y] = 3;
			}
		}
	}

}
std::unordered_map<int, std::unordered_map<int, int>> RandomDungeonRoom::getRoomData() {
	return this->_map_data;
}
int RandomDungeonRoom::getRoadPositionLeft() {
	return this->_load_position_left + this->_room_y;
}
int RandomDungeonRoom::getRoadPositionRight() {
	return this->_load_position_right + this->_room_y;
}
int RandomDungeonRoom::getRoadPositionTop() {
	return this->_load_position_top + this->_room_x;
}
int RandomDungeonRoom::getRoadPositionBottom() {
	return this->_load_position_bottom + this->_room_x;
}
void RandomDungeonRoom::joinRoad(randomRoadType road_type, int position_point) {
	int roop_num = 0;
	switch (road_type) {
	case randomRoadType::left:
		roop_num = this->getRoadPositionLeft() - position_point;
		if (roop_num < 0) {
			roop_num = roop_num * (-1);
		}
		for (int i = 0; i < roop_num; i++) {
			if (this->getRoadPositionLeft() > position_point) {
				this->_map_data[0][this->getRoadPositionLeft() - (i + 1)] = 4;
			}
			else if (this->getRoadPositionRight() < position_point) {
				this->_map_data[0][this->getRoadPositionLeft() + (i + this->_road_size)] = 4;
			}
		}
		break;
	case randomRoadType::right:
		roop_num = this->getRoadPositionRight() - position_point;
		if (roop_num < 0) {
			roop_num = roop_num * (-1);
		}
		for (int i = 0; i < roop_num; i++) {
			if (this->getRoadPositionRight() > position_point) {
				this->_map_data[this->_dungeon_map_x - 1][this->getRoadPositionRight() - (i + 1)] = 4;
			}
			else if (this->getRoadPositionRight() < position_point) {
				this->_map_data[this->_dungeon_map_x - 1][this->getRoadPositionRight() + (i + this->_road_size)] = 4;
			}
		}
		break;
	case randomRoadType::top:
		roop_num = this->getRoadPositionTop() - position_point;
		if (roop_num < 0) {
			roop_num = roop_num * (-1);
		}
		for (int i = 0; i < roop_num; i++) {
			if (this->getRoadPositionTop() > position_point) {
				this->_map_data[this->getRoadPositionTop() - (i + 1)][0] = 4;
			}
			else if (this->getRoadPositionTop() < position_point) {
				this->_map_data[this->getRoadPositionTop() + (i + this->_road_size)][0] = 4;
			}
		}
		break;
	case randomRoadType::bottom:
		roop_num = this->getRoadPositionBottom() - position_point;
		if (roop_num < 0) {
			roop_num = roop_num * (-1);
		}
		for (int i = 0; i < roop_num; i++) {
			if (this->getRoadPositionBottom() > position_point) {
				this->_map_data[this->getRoadPositionBottom() - (i + 1)][this->_dungeon_map_y - 1] = 4;
			}
			else if (this->getRoadPositionBottom() < position_point) {
				this->_map_data[this->getRoadPositionBottom() + (i + this->_road_size)][this->_dungeon_map_y - 1] = 4;
			}
		}
		break;
	}
}