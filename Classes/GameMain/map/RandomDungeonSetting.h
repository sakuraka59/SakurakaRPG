#pragma once

#include "../../Random.h"

class RandomDungeonSetting{
// 共通設定 -----------------------------------------------------
// road width
public: static const int _ROAD_WIDTH = 3;

// 部屋作成のアルゴリズムの指定
// 1：ローグライクにおける部屋分割法による作成
// 2：ランダム地点選択からの部屋展開による作成
public: static const int _MAP_CREATE_TYPE = 2;

// 1：ローグライクにおける部屋分割法による作成 ------------------
// room num
public: static const int _DUNGEON_BLOCK_X = 7;
public: static const int _DUNGEON_BLOCK_Y = 5;

// room width and height
public: static const int _DUNGEON_MAP_X = 15;//15;
public: static const int _DUNGEON_MAP_Y = 10;//9;
public: static const int _ROOM_FRAME_SIZE = 2;

// 2：ランダム地点選択からの部屋展開による作成にて使用 ----------
// map size
public: static const int _MAP_WIDTH = 16 * 3;
public: static const int _MAP_HEIGHT = 9 * 3;
public: static const int _MAP_FRAME_NUM = 1;

// 部屋数
public: static const int _ROOM_MIN = 5;
public: static const int _ROOM_MAX = 8;

// 1つあたりの部屋の大きさ
public: static const int _ROOM_MIN_WIDTH = 12;
public: static const int _ROOM_MIN_HEIGHT = 6;
public: static const int _ROOM_MAX_WIDTH = 16;
public: static const int _ROOM_MAX_HEIGHT = 9;

// 宝箱設定
public: static const int _ITEM_BOX_MIN = 0;	// 最低数
public: static const int _ITEM_BOX_MAX = 4;	// 最大数
//-------------------------------------------------------------------
public: static int getDungeonWidth() {
	int dungeon_width = 0;
	switch (RandomDungeonSetting::_MAP_CREATE_TYPE) {
	case 1:
		dungeon_width = RandomDungeonSetting::_DUNGEON_MAP_X * RandomDungeonSetting::_DUNGEON_BLOCK_X;
		break;
	case 2:
		dungeon_width = RandomDungeonSetting::_MAP_WIDTH + (RandomDungeonSetting::_MAP_FRAME_NUM * 2);
		break;
	}
	return dungeon_width;
}
public: static int getDungeonHeight() {
	int dungeon_height = 0;
	switch (RandomDungeonSetting::_MAP_CREATE_TYPE) {
	case 1:
		dungeon_height = RandomDungeonSetting::_DUNGEON_MAP_Y * RandomDungeonSetting::_DUNGEON_BLOCK_Y;
		break;
	case 2:
		dungeon_height = RandomDungeonSetting::_MAP_HEIGHT + (RandomDungeonSetting::_MAP_FRAME_NUM * 2);
		break;
	}
	return dungeon_height;
}
public: static int getItemBoxNum() {
	int item_box_num = 0;
	int rand_num = RandomDungeonSetting::_ITEM_BOX_MAX + RandomDungeonSetting::_ITEM_BOX_MIN - 1;
	Random* rand_obj = new Random();
	switch (RandomDungeonSetting::_MAP_CREATE_TYPE) {
	case 2:
		if (rand_num > 0) {
			item_box_num = RandomDungeonSetting::_ITEM_BOX_MIN + rand_obj->getRandNum(rand_num);
		} else {
			item_box_num = RandomDungeonSetting::_ITEM_BOX_MIN;
		}
		break;
	}
	return item_box_num;
}
};