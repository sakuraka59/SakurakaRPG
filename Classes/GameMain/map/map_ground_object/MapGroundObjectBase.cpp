#include "MapGroundObjectBase.h"
#include "../../GAME_SETTING.h"
#include "../../hit/HitSquare.h"
#include "../../chara/CharaBase.h"

MapGroundObjectBase::MapGroundObjectBase(int map_block_x, int map_block_y) {
	this->_draw_x = (map_block_x * MAP_BLOCK_WIDTH);
	this->_draw_y = (map_block_y * MAP_BLOCK_HEIGHT);

	double test_angle = 0;

	this->_sprite_img_pass = "img/map/ground/test_load.png";
	this->_sprite_data = Sprite::create(this->_sprite_img_pass);

	int poitn_x_correct = (this->_OBJECT_CORRECT_WIDTH - MAP_BLOCK_WIDTH) / 2;
	this->_sprite_data->setPosition((float)((MAP_BLOCK_WIDTH / 2) - poitn_x_correct), (float)(MAP_BLOCK_HEIGHT / 2));


	this->_hit_square_obj = new HitSquare(this->_draw_x, this->_draw_y, MAP_BLOCK_WIDTH, MAP_BLOCK_HEIGHT, test_angle);

	
	this->setPosition((float)this->_draw_x, (float)this->_draw_y);

	this->addChild(this->_sprite_data);


	// TEST
	this->_hit_flag = true;
}
void MapGroundObjectBase::Update() {
}
void MapGroundObjectBase::UpdateInit() {
	this->_before_chara_list =  this->_active_chara_list;
	this->_active_chara_list.clear();
}
HitSquare* MapGroundObjectBase::getHitSquare() {
	return this->_hit_square_obj;
}
bool MapGroundObjectBase::getHitFlag() {
	return this->_hit_flag;
}
bool MapGroundObjectBase::getActionFlag() {
	return this->_action_flag;
}



void MapGroundObjectBase::autoActive(CharaBase* chara_obj) {
	// TEST
//	this->autoPushActive(chara_obj);
//	this->autoPressActive(chara_obj);
	this->autoOnlyActive(chara_obj);
}
void MapGroundObjectBase::autoPushActive(CharaBase* chara_obj) {
	if (chara_obj->checkGroundFlag() != true) {
		return;
	}
	if (this->_before_chara_list.find(chara_obj) == this->_before_chara_list.end()) {
		this->autoObjBehavior(chara_obj);
	}
	this->_active_chara_list[chara_obj] = true;
}
void MapGroundObjectBase::autoPressActive(CharaBase* chara_obj) {
	if (chara_obj->checkGroundFlag() != true) {
		return;
	}
	this->autoObjBehavior(chara_obj);
}
void MapGroundObjectBase::autoOnlyActive(CharaBase* chara_obj) {
	if (chara_obj->checkGroundFlag() != true) {
		return;
	}
	this->_hit_flag = false;
	this->autoObjBehavior(chara_obj);
}
void MapGroundObjectBase::autoObjBehavior(CharaBase* chara_obj) {
	chara_obj->sendComment("どーん！");
	chara_obj->healHp(1);
}


void MapGroundObjectBase::actionActive(CharaBase* chara_obj) {
	// TEST
	//	this->actionPushActive(chara_obj);
	this->actionOnlyActive(chara_obj);

}
void MapGroundObjectBase::actionPushActive(CharaBase* chara_obj) {
	if (chara_obj->checkGroundFlag() != true) {
		return;
	}
	if (this->getActionFlag() == true) {
		this->actionObjBehavior(chara_obj);
	}
}
void MapGroundObjectBase::actionOnlyActive(CharaBase* chara_obj) {
	if (chara_obj->checkGroundFlag() != true) {
		return;
	}
	if (this->getActionFlag() == true) {
		this->_action_flag = false;
		this->actionObjBehavior(chara_obj);
	}
}
void MapGroundObjectBase::actionObjBehavior(CharaBase* chara_obj) {
	chara_obj->sendComment("どーん！");
	chara_obj->healHp(1);
}
