#include "MapGroundBase.h"

#include "cocos2d.h"
#include "../GAME_SETTING.h"


MapGroundBase::MapGroundBase(int block_x, int block_y, int map_width, int map_height, int test_type) {

	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create("/img/test_dot.png");
	sprite_data->setScale(MAP_BLOCK_WIDTH, MAP_BLOCK_HEIGHT);
	this->addChild(sprite_data);
	this->_draw_x = block_x * MAP_BLOCK_WIDTH;
	this->_draw_y = block_y * MAP_BLOCK_HEIGHT;
	this->setPosition( (float)this->_draw_x,(float)this->_draw_y);
}