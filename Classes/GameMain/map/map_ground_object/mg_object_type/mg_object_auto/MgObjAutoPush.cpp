#include "MgObjAutoPush.h"
#include "../../../../chara/CharaBase.h"
MgObjAutoPush::MgObjAutoPush(int map_block_x, int map_block_y) : MgObjectAuto(map_block_x, map_block_y){

}
void MgObjAutoPush::UpdateInit() {
	this->_active_chara_list.clear();
}
void MgObjAutoPush::activeObject(CharaBase* chara_obj) {
	chara_obj->sendComment("‚Ç[‚ñI");
	chara_obj->healHp(1);
}