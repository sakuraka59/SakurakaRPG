#include "MiniMapBase.h"

MiniMapBase::MiniMapBase(){

}
void MiniMapBase::loadMapData() {

}
unordered_map<int, std::unordered_map<int, int>> MiniMapBase::getMapData() {

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