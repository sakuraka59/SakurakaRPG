#include "MapMove.h"
#include "../../../../chara/CharaBase.h"
#include "MapMoveManager.h"

MapMove::MapMove(int map_block_x, int map_block_y, MapMoveData* map_move_data) : MapGroundObjectBase(map_block_x, map_block_y) {

	this->_map_move_data = map_move_data;
	// TEST
	this->_hit_flag = true;
	this->_action_flag = true;
}

void MapMove::actionObjBehavior(CharaBase* chara_obj) {
	chara_obj->sendComment("‚Ç[‚ñII");
	chara_obj->healHp(1000);

//	MapMoveManager::setMapMoveData(this->_map_move_data);
}
void MapMove::Update() {

}