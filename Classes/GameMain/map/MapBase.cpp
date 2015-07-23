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

#include "map_ground_object/MapGroundObjectList.h"

#include "map_ground_object/map_bg_obj/map_move/MapMoveManager.h"

// テスト
#include "mini_map\test_map\TestMap.h"

MapBase::MapBase(GameCamera* camera_obj, CharaPlayer* player_obj) {
	this->_player_obj = player_obj;
	
	this->_camera_obj = camera_obj;
	

	// DEBUG --------------------------
	// ランダムマップ
//	this->createRandomMap();

	// 固定ミニマップ
	this->createMiniMap();

	// ワールドマップ
}
void MapBase::Init() {
	this->_map_ground_obj->Init();
	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {	
		this->_map_obj_line_list[map_obj_iterator->first]->mapSetDrawInit();
	}
}
void MapBase::Update() {
	MapMoveManager::updateInit();

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
/*
std::unordered_map<int, std::unordered_map<int, MapObjectBase*>> MapBase::getMapObjectList() {
	return this->_map_obj_list;
}
*/
void MapBase::initMapObject(std::unordered_map<int, std::unordered_map<int, int>> map_data) {
	
	if (SET_MAP_MODE == 1) {
		return;
	}
	
//	int map_width = RandomDungeonSetting::getDungeonWidth();
//	int map_height = RandomDungeonSetting::getDungeonHeight();
	
	int map_width = map_data.size();
	int map_height = map_data[0].size();

	for (int x = 0; x < map_width; x++) {
		int set_x = x;
				
				
		for (int y = 0; y < map_height; y++) {
			int set_y = y * (-1);

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
	int hoge = 1;
	//*/
}
std::unordered_map<int, MapObjectList*> MapBase::getMapObjectLineList() {
	return this->_map_obj_line_list;
}
MapGroundObjectList* MapBase::getMgObjectList() {
	return this->_mg_object_list_obj;
}
//-------------------------------------------------------------------
//	ランダムマップを作成
//-------------------------------------------------------------------
void MapBase::createRandomMap() {


//	this->_map_base_data;

	this->_map_type = 1;

	RandomDungeon* get_dungeon_obj = new RandomDungeon();
	this->_map_base_data = get_dungeon_obj->getMapData();
	this->_map_ground_data = get_dungeon_obj->getMapGroundData();



	this->_map_ground_obj = new MapGroundList(this->_map_ground_data, 1, this->_player_obj);

	this->_mg_object_list_obj = new MapGroundObjectList(this->_player_obj);
	/*
	std::unordered_map<int, std::unordered_map<int, int>> test_map;
	this->_map_ground_obj = new MapGroundList(this->_camera_obj, test_map, 0, this->_player_obj);
	// */

	this->addChild(this->_map_ground_obj,1);
	this->setCharaPoint(this->_player_obj, 2);

	// マップ移動用設置オブジェクト読み込み
	list<MapMove*> map_move_obj_list;
	MapMoveData* move_data_1 = new MapMoveData(3, 0, 0, 1, 0);
	map_move_obj_list.push_back(new MapMove(this->_player_obj->getMapBlockX(), (this->_player_obj->getMapBlockY()), move_data_1));

	this->_mg_object_list_obj->LoadMapMoveData(map_move_obj_list);

	this->_mg_object_list_obj->loadEnd();
	// map obj ----------------------------------------------
	this->initMapObject(get_dungeon_obj->getMapData());

	// DEBUG 
	this->addChild(this->_mg_object_list_obj,2);
}
//-------------------------------------------------------------------
//	固定ミニマップ作成
//-------------------------------------------------------------------
void MapBase::createMiniMap(){
	this->_map_type = 2;
	this->_map_ground_obj = nullptr;
	
//	this->_mg_object_list_obj = nullptr;


	MiniMapManager::loadMiniMap(miniMapType::test_map);

	this->_map_ground_data = MiniMapManager::getMapData();
	this->_map_ground_obj = new MapGroundList(this->_map_ground_data, 2, this->_player_obj);
	

	this->_mg_object_list_obj = new MapGroundObjectList(this->_player_obj);
	
	// マップ移動用設置オブジェクト読み込み
	this->_mg_object_list_obj->LoadMapMoveData(MiniMapManager::getMapMoveObjData());

	// 設置オブジェクト読み込み
	this->_mg_object_list_obj->LoadData(MiniMapManager::getMapGroundObjData());

	this->_mg_object_list_obj->loadEnd();

	this->addChild(this->_map_ground_obj,1);
	this->addChild(this->_mg_object_list_obj,2);

	this->initMapObject(this->_map_ground_data);

	// 操作キャラ配置
	int chara_room_x = 2;
	int chara_room_y = 2;
	double chara_x = MAP_BLOCK_WIDTH * chara_room_x + (MAP_BLOCK_WIDTH / 2);
	double chara_y = (MAP_BLOCK_HEIGHT * chara_room_y - (MAP_BLOCK_HEIGHT / 2)) * (-1);
	this->_player_obj->setCharaMapPoint(chara_x, chara_y);
	int chara_block_x = this->_player_obj->getMapBlockX();
	int chara_block_y = this->_player_obj->getMapBlockY();



//	this->_map_ground_obj = new MapGroundList(this->_camera_obj, get_dungeon_obj->getMapData(), 1, this->_player_obj);

}


void MapBase::setCharaPoint(CharaBase* set_chara_obj, int map_block_type) {

	//*
	if (this->_map_type != 1) {
		return;
	}
	// @TODO ランダムMAPのみ対応。
//	int map_width = RandomDungeonSetting::getDungeonWidth();
//	int map_height = RandomDungeonSetting::getDungeonHeight();

	int map_width = this->_map_base_data.size();
	int map_height = this->_map_base_data[0].size();

	std::unordered_map<int, std::unordered_map<int, int>> map_base_data = this->_map_base_data;
	int room_block_count = 0;

	int check_map_type = map_block_type;
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {

			if (map_base_data[x][y] == check_map_type) {
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

			if (map_base_data[x][y] == check_map_type) {
				//Debug.WriteLine("check :"+ x +":"+ y);
				if (chara_room_num == check_room_block_count) {
					chara_room_x = x;
					chara_room_y = y;


					// DEBUG ------------------------------
//					chara_room_x = 10;
					//					chara_room_y = 5;
					if (SET_MAP_MODE == 1) {
						chara_room_x = 1;
						chara_room_y = 1;
					}

					//Debug.WriteLine("set :"+ chara_room_x +":"+ chara_room_y);
					double chara_x = MAP_BLOCK_WIDTH * chara_room_x + (MAP_BLOCK_WIDTH / 2);
					double chara_y = (MAP_BLOCK_HEIGHT * chara_room_y - (MAP_BLOCK_HEIGHT / 2)) * (-1);

					// DEBUG ------------------------------




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
// マップ移動処理
void MapBase::mapMoveUpdate() {
	if (MapMoveManager::checkMapMove() != true) {
		int hoge = 1;
		return;
	}
	

	MapMoveData* map_move_obj = MapMoveManager::getMapMoveData();
	if (map_move_obj == nullptr) {
		return;
	}

	// まずは初期化
	this->_map_ground_obj->removeAllChildren();
	this->_mg_object_list_obj->removeAllChildren();
	this->_map_obj_line_list.clear();

	this->_map_ground_obj = nullptr;
	this->_mg_object_list_obj = nullptr;


	switch (map_move_obj->getMoveType()) {
	case 1:	// ワールドマップ移動
		// @TODO そもそも未実装
		break;
	case 2:	// ミニマップ移動

		break;
	case 3:	// ランダムマップ移動
		this->createRandomMap();
		break;
	}


	return;
}