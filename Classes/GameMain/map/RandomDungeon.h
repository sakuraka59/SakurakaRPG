#pragma once

#include <unordered_map>
#include <random>
#include "RandomDungeonSetting.h"

class Random;

class RandomDungeon {
private: std::unordered_map<int, std::unordered_map<int, int>> _map_data;
private: Random* _rand_obj;
public: RandomDungeon();

// 部屋分割法でマップ作成
private: void DungeonCreateRogelike(int dungeon_width, int dungeon_height);

// 独自処理でマップ作成
private: void DungeonCreateOriginal(int dungeon_width, int dungeon_height);

// マス指定による、部屋を作成
private: void setRoomExpansion(int room_core_x, int room_core_y);

// マス指定による、道を作れるか検索
private: void setRoadFirstRoom(int room_core_x, int room_core_y);

// マス指定による、道を作れるか検索(簡易版
private: bool setRoadSearchMin(int room_core_x, int room_core_y, int first_core_x, int first_core_y);

//	通路を作成できるかチェック
//	部屋の中心地から通路を延ばし、通路が曲がって別の部屋や通路に繋がるかチェック
private: void checkRoadCreate(int room_core_x, int room_core_y, int first_core_x, int first_core_y, int road_type, int sub_road_type);

//	通路を作成できるかチェック
//	簡易版なので部屋の中心地から通路を延ばして別の部屋や通路に繋がるかチェック
private: bool checkRoadCreateMini(int room_core_x, int room_core_y, int first_core_x, int first_core_y, int road_type);

// 通路作成チェック。ランダム版
private: bool checkRoadCreateRandom(int room_core_x, int room_core_y);

// 通路作成チェック。ランダム版の詳細処理
private: bool checkRoadCreateMiniDetail(int room_core_x, int room_core_y, int main_load_search_num, int road_type, std::unordered_map<int, std::unordered_map<int, int>>map_search_data);


// 通路を作成
private: void setRoadExpansion(int room_core_x, int room_core_y, int road_type, int road_num);

private: void setMapData(int expansion_x, int expansion_y, int map_type);

public: std::unordered_map<int, std::unordered_map<int, int>> getMapData();

private: int getMapDataFreeNum();

private: int getMapBlockNum();
};