#include "MapBase.h"
#include "../GameCamera.h"
#include "../chara/CharaPlayer.h"
#include "../chara/CharaBase.h"
#include "MapGroundList.h"
#include "MapObjectList.h"
#include "../GAME_SETTING.h"
#include <math.h>
#include "RandomDungeon.h"

#include "../../Random.h"

#include "mini_map/MiniMapManager.h"
#include "mini_map/miniMapType.h"

// テスト
#include "mini_map\test_map\TestMap.h"

MapBase::MapBase(GameCamera* camera_obj, CharaPlayer* player_obj) {
	this->_player_obj = player_obj;
	
	this->_camera_obj = camera_obj;
	

	// ランダムマップ
	this->createRandomMap();

	// 固定ミニマップ
//	this->createMiniMap();

	// ワールドマップ
}
void MapBase::Init() {
	this->_map_ground_obj->Init();
	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {	
		this->_map_obj_line_list[map_obj_iterator->first]->mapSetDrawInit();
	}
}
void MapBase::Update() {
	this->_map_ground_obj->Update();


	/*
	//	Debug.WriteLine("[MapBase]-------------------------------------------");
	foreach(KeyValuePair<int, Dictionary<int, MapObjectBase>> list_pair in this._map_obj_list) {
		foreach(KeyValuePair<int, MapObjectBase> pair in list_pair.Value) {
			pair.Value.Update();
		}
	}
	//*/

	/*
	foreach(KeyValuePair<int, MapObjectList> pair in this._map_obj_line_list) {
		pair.Value.Update();
	}
	// */

	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {
//		std::pair<int, MapObjectList*> map_obj_line = *map_obj_iterator;
		this->_map_obj_line_list[map_obj_iterator->first]->Update();
//		map_obj_line;

	}
}
std::unordered_map<int, std::unordered_map<int, MapObjectBase*>> MapBase::getMapObjectList() {
	return this->_map_obj_list;
}
void MapBase::initMapObject(std::unordered_map<int, std::unordered_map<int, int>> map_data) {
	
	if (SET_MAP_MODE == 1) {
		return;
	}
//		TextureInfo test_texture_info = ResourceManage.getTextureInfo("/Application/res/Objects.png",7,3);

//		this->_map_obj_list[0] = new Dictionary<int, MapObjectBase>();
//Debug.WriteLine("[MapBase]initMapObject");
			
	// map get to width and height
	/*
	int map_width = map_data.GetLength(0);
	int map_height = map_data.GetLength(1);
	*/
	int map_width = RandomDungeonSetting::getDungeonWidth();
	int map_height = RandomDungeonSetting::getDungeonHeight();
		

	for (int x = 0; x < map_width; x++) {
		int set_x = x;
				
				
		for (int y = 0; y < map_height; y++) {
			int set_y = y * (-1);
			int hoge = map_data[set_x][y];
			if (map_data[set_x][y] == 1 || map_data[set_x][y] == 5) {
				
				if (this->_map_obj_line_list[set_y] == nullptr) {
					MapObjectList* map_obj_list = new MapObjectList(
						set_y,
						this->_camera_obj,
						this->_player_obj
					);
					this->_map_obj_line_list[set_y] = map_obj_list;
				}
				this->_map_obj_line_list[set_y]->setObject(set_x);
			}
		}
	}
	//*/
}
std::unordered_map<int, MapObjectList*> MapBase::getMapObjectLineList() {
	return this->_map_obj_line_list;
}
//-------------------------------------------------------------------
//	ランダムマップを作成
//-------------------------------------------------------------------
void MapBase::createRandomMap() {
	this->_map_type = 1;
	RandomDungeon* get_dungeon_obj = new RandomDungeon();
	this->_map_data = get_dungeon_obj->getMapData();
	this->_map_ground_data = get_dungeon_obj->getMapGroundData();



	this->_map_ground_obj = new MapGroundList(this->_map_ground_data, 1, this->_player_obj);
	/*
	std::unordered_map<int, std::unordered_map<int, int>> test_map;
	this->_map_ground_obj = new MapGroundList(this->_camera_obj, test_map, 0, this->_player_obj);
	// */

	this->addChild(this->_map_ground_obj);
	this->setCharaPoint(this->_player_obj, 2);
	// map obj ----------------------------------------------
	this->initMapObject(get_dungeon_obj->getMapData());

}
//-------------------------------------------------------------------
//	固定ミニマップ作成
//-------------------------------------------------------------------
void MapBase::createMiniMap(){
	this->_map_type = 2;
	MiniMapManager::loadMiniMap(miniMapType::test_map);
//	auto map_data = MiniMapManager::getMapData();

//	this->_map_data = get_dungeon_obj->getMapData();
	this->_map_ground_data = MiniMapManager::getMapData();

	/*
	TestMap* test_map_obj = new TestMap();
	auto map_data = test_map_obj->getMapData();
	*/
	this->_map_ground_obj = new MapGroundList(this->_map_ground_data, 2, this->_player_obj);

//	this->createRandomMap();

	this->addChild(this->_map_ground_obj);

//	this->setCharaPoint(this->_player_obj, 2);

//	this->initMapObject(map_data);

	this->_player_obj->setCharaMapPoint(0, 0);
	int chara_block_x = this->_player_obj->getMapBlockX();
	int chara_block_y = this->_player_obj->getMapBlockY();
//	this->_map_ground_obj = new MapGroundList(this->_camera_obj, get_dungeon_obj->getMapData(), 1, this->_player_obj);

//	this->addChild(this->_map_ground_obj);
}


void MapBase::setCharaPoint(CharaBase* set_chara_obj, int map_block_type) {

	//*
	if (this->_map_type != 1) {
		return;
	}
	// @TODO ランダムMAPのみ対応。
	int map_width = RandomDungeonSetting::getDungeonWidth();
	int map_height = RandomDungeonSetting::getDungeonHeight();

	std::unordered_map<int, std::unordered_map<int, int>> map_data = this->_map_data;
	int room_block_count = 0;

	int check_map_type = map_block_type;
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {

			if (map_data[x][y] == check_map_type) {
				room_block_count++;

			}
		}
	}
	if (room_block_count <= 0) {
		return;
	}
	Random* rand_obj = new Random();

	int chara_room_x = 0;
	int chara_room_y = 0;
	int chara_room_num = 0;
	int check_room_block_count = 0;

	chara_room_num = rand_obj->getRandNum(room_block_count - 1);

	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {

			if (map_data[x][y] == check_map_type) {
				//Debug.WriteLine("check :"+ x +":"+ y);
				if (chara_room_num == check_room_block_count) {
					chara_room_x = x;
					chara_room_y = y;


					// test
					//					chara_room_x = 10;
					//					chara_room_y = 5;
					if (SET_MAP_MODE == 1) {
						chara_room_x = 1;
						chara_room_y = 1;
					}

					//Debug.WriteLine("set :"+ chara_room_x +":"+ chara_room_y);
					double chara_x = MAP_BLOCK_WIDTH * chara_room_x + (MAP_BLOCK_WIDTH / 2);
					double chara_y = (MAP_BLOCK_HEIGHT * chara_room_y - (MAP_BLOCK_HEIGHT / 2)) * (-1);

					set_chara_obj->setCharaMapPoint(chara_x, chara_y);
					int chara_block_x = set_chara_obj->getMapBlockX();
					int chara_block_y = set_chara_obj->getMapBlockY();
					delete rand_obj;
					return;
				}
				else {
					check_room_block_count++;
				}
			}
		}
	}

	delete rand_obj;
	// */
}