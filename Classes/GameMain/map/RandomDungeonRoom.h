#pragma once
#include <unordered_map>

class Random;
enum class randomRoadType;

class RandomDungeonRoom {
private: std::unordered_map<int, std::unordered_map<int, int>> _map_data;

private: int _room_width = 0;
private: int _room_height = 0;
private: int _room_x = 0;
private: int _room_y = 0;
private: int _road_size = 0;

private: int _load_position_left = -1;
private: int _load_position_top = -1;
private: int _load_position_right = -1;
private: int _load_position_bottom = -1;

// to debug
private: int _dungeon_map_x = 0;
private: int _dungeon_map_y = 0;

private: Random* _rand_obj;

public: RandomDungeonRoom (int room_width_max, int room_height_max, int road_size,
		int dungeon_map_x, int dungeon_map_y, int map_frame_size, Random* rand_obj);

public: void setDungeonRoad(int room_block_x, int room_block_y, int dungeon_block_x, int dungeon_block_y);
public: std::unordered_map<int, std::unordered_map<int, int>> getRoomData();

public: int getRoadPositionLeft();
public: int getRoadPositionRight();
public: int getRoadPositionTop();
public: int getRoadPositionBottom();
public: void joinRoad(randomRoadType road_type, int position_point = -1);
};