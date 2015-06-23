#include "MiniMapBase.h"

MiniMapBase::MiniMapBase(){

}

unordered_map<int, unordered_map<int, int>> MiniMapBase::getMapData() {

	if (this->_load_map_data == true) {
		return this->_map_data;
	}

	int y = 0;
	for (list<int> map_data_base : this->_map_data_base) {
		int x = 0;

		for (int map_data : map_data_base) {
			this->_map_data[x][y] = map_data;
			x++;
		}

		y++;
	}
	this->_load_map_data = true;
	return this->_map_data;
}
unordered_map<int, MapObjectList*> MiniMapBase::getMapObjData() {
	return this->_map_obj_line_list;
}

unordered_map<int, unordered_map<int, int>> MiniMapBase::getMapGoundObjData() {
	if (this->_load_map_ground_obj == true) {
		return this->_map_data;
	}

	int y = 0;
	for (list<int> map_obj_base : this->_map_ground_obj_base) {
		int x = 0;

		for (int map_obj_data : map_obj_base) {
			this->_map_ground_obj_list[x][y] = map_obj_data;
			x++;
		}

		y++;
	}
	this->_load_map_ground_obj = true;
	;
	return this->_map_ground_obj_list;
}
list<MapMove*> MiniMapBase::getMapMoveObjData() {
	return this->_map_move_obj_list;
}