#include "MapGroundObjectList.h"
#include "MapGroundObjectBase.h"

#include "map_bg_obj/MapMove.h"

MapGroundObjectList::MapGroundObjectList(CharaPlayer* player_obj) {
	this->_player_obj = player_obj;

	this->_ground_sprite_list = new RenderObject();
}
void MapGroundObjectList::LoadMapMoveData(list<MapMove*> map_move_obj_list) {


	for (MapMove* map_move_obj : map_move_obj_list) {
		int map_block_x = map_move_obj->getMapBlockX();
		int map_block_y = map_move_obj->getMapBlockY();

		// map_block_yが元々マイナス値のため、LoadMapとはmap_block_yの扱いが違うので注意
		this->_ground_obj_list[map_block_x][map_block_y] = map_move_obj;
		this->_map_draw_list[map_block_x][map_block_y] = false;

		this->_ground_sprite_list->addChild(this->_ground_obj_list[map_block_x][map_block_y]);
	}
	/*
	this->_ground_obj_list[map_search_x][map_search_y * (-1)] = ground_obj;
	this->_map_draw_list[map_search_x][(map_search_y * (-1))] = false;

	// @TODO とりあえず全表示
	this->_ground_sprite_list->addChild(this->_ground_obj_list[map_search_x][map_search_y * (-1)]);
	*/
}
void MapGroundObjectList::LoadData(unordered_map<int, unordered_map<int, int>> map_ground_data) {
	this->_map_ground_obj_data = map_ground_data;

//	this->_ground_sprite_list->removeAllChildrenWithCleanup();

	int map_width = this->_map_ground_obj_data.size();
	int map_height = this->_map_ground_obj_data[0].size();
	

	for (int map_search_x = 0; map_search_x < map_width; map_search_x++) {
		int map_search_y = 0;
		for (int map_search_y = 0; map_search_y < map_height; map_search_y++) {
			if (this->_map_ground_obj_data[map_search_x][map_search_y] < 1) {
				continue;
			}
			if (this->_ground_obj_list[map_search_x][map_search_y * (-1)] != nullptr) {
				continue;
			}
			// @TODO 後で読み込み用マネージャを作成して、そちらから読み込むようにする
			MapGroundObjectBase* ground_obj = new MapGroundObjectBase(
				map_search_x, map_search_y * (-1)
				);		
			this->_ground_obj_list[map_search_x][map_search_y * (-1)] = ground_obj;
			this->_map_draw_list[map_search_x][(map_search_y * (-1))] = false;

			// @TODO とりあえず全表示
			this->_ground_sprite_list->addChild(this->_ground_obj_list[map_search_x][map_search_y * (-1)]);
		}
	}
	this->_ground_sprite_list->setPosition(0, 0);
	this->addChild(this->_ground_sprite_list);
}
void MapGroundObjectList::Init() {

}
void MapGroundObjectList::UpdateInit() {
	int map_width = this->_map_ground_obj_data.size();
	int map_height = this->_map_ground_obj_data[0].size();


	for (int map_search_x = 0; map_search_x < map_width; map_search_x++) {
		int map_search_y = 0;
		for (int map_search_y = 0; map_search_y < map_height; map_search_y++) {
			if (this->_map_ground_obj_data[map_search_x][map_search_y] < 1) {
				continue;
			}
			this->_ground_obj_list[map_search_x][map_search_y * (-1)]->UpdateInit();
		}
	}
}
void MapGroundObjectList::Update() {
	int map_width = this->_map_ground_obj_data.size();
	int map_height = this->_map_ground_obj_data[0].size();


	for (int map_search_x = 0; map_search_x < map_width; map_search_x++) {
		int map_search_y = 0;
		for (int map_search_y = 0; map_search_y < map_height; map_search_y++) {
			if (this->_map_ground_obj_data[map_search_x][map_search_y] < 1) {
				continue;
			}
			this->_ground_obj_list[map_search_x][map_search_y * (-1)]->Update();
		}
	}
}
void MapGroundObjectList::reviewGroundBlockX(int add_block_draw_x, int remove_block_draw_x, int block_draw_y, int map_max_y) {

}
void MapGroundObjectList::reviewGroundBlockY(int add_block_draw_y, int remove_block_draw_y, int block_draw_x, int map_max_x) {

}
unordered_map<int, unordered_map<int, MapGroundObjectBase*>> MapGroundObjectList::getGroundObjData() {
	return this->_ground_obj_list;
}