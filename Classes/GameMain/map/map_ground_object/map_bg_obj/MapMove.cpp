#include "MapMove.h"
#include "../../../chara/CharaBase.h"

MapMove::MapMove(int map_block_x, int map_block_y, int map_move_type) : MapGroundObjectBase(map_block_x, map_block_y) {
	// TEST
	this->_hit_flag = true;
	this->_action_flag = true;
}

void MapMove::actionObjBehavior(CharaBase* chara_obj) {
	chara_obj->sendComment("‚Ç[‚ñII");
	chara_obj->healHp(1000);
}