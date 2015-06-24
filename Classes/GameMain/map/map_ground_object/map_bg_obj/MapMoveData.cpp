#include "MapMoveData.h"


MapMoveData::MapMoveData(int map_move_type, int move_block_x, int move_block_y, int extend_data_1, int extend_data_2) {
	this->_map_move_type = map_move_type;
	this->_move_block_x = move_block_x;
	this->_move_block_y = move_block_y;
	this->_extend_data_1 = extend_data_1;
	this->_extend_data_2 = extend_data_2;
}
int MapMoveData::getMoveType() {
	return this->_map_move_type;
}
int MapMoveData::getMoveBlockX() {
	return this->_move_block_x;
}
int MapMoveData::getMoveBlockY() {
	return this->_move_block_y;
}
int MapMoveData::getExtendData1() {
	return this->_extend_data_1;
}
int MapMoveData::getExtendData2() {
	return this->_extend_data_2;
}