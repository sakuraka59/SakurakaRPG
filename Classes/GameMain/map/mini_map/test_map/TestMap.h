#pragma once
#include "../MiniMapBase.h"
#include "../../map_ground_object/map_bg_obj/map_move/MapMove.h"
#include "../../map_ground_object/map_bg_obj/map_move/MapMoveData.h"


#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
class MapObjectList;


class TestMap : public MiniMapBase {
public: TestMap() {

	/*
	list<list<int>>map_data{
		{ 1, 5, 5, 5, 5, 1, 5, 5, 5, 5, 1, 1 },
		{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },
		{ 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1 },
	};
	*/

	list<list<int>>map_data{
		{ 3, 5, 5, 5, 5, 1, 5, 5, 5, 5, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	};
	this->_map_data_base = map_data;
	list<list<int>>map_ground_obj_data{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	this->_map_ground_obj_base = map_ground_obj_data;

	MapMoveData* move_data_1 = new MapMoveData(3, 0, 0, 1, 0);
	this->_map_move_obj_list.push_back(new MapMove(5, -9, move_data_1));
	this->_map_move_obj_list.push_back(new MapMove(6, -9, move_data_1));
	//this->_map_move_obj_list.push_back(new MapMove(1, 6, 9));
}

};