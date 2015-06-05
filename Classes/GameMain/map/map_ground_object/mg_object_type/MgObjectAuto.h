#pragma once
#include "../MapGroundObjectBase.h"


class MgObjectAuto : public MapGroundObjectBase {
public: MgObjectAuto(int map_block_x, int map_block_y) : MapGroundObjectBase(map_block_x, map_block_y) {
	this->_hit_flag = true;
}
public: void activeObject(CharaBase* chara_obj) override;
};