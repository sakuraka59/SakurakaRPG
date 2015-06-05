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
}
void MapGroundObjectBase::Update() {

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

void MapGroundObjectBase::activeObject(CharaBase* chara_obj) {

}