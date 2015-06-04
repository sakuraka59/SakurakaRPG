#include "MapGroundBase.h"

#include "cocos2d.h"
#include "../GAME_SETTING.h"

#include "mapGroundType.h"

MapGroundBase::MapGroundBase(int block_x, int block_y, int ground_type) {


	std::string image_pass = "img/map/ground/test_grass1.png";
	switch (ground_type) {
	case (int)mapGroundType::grass: //‘’n
		image_pass = "img/map/ground/test_grass1.png";
		break;
	case (int)mapGroundType::new_load: //ŒÃ‚¢“¹˜H
		image_pass = "img/map/ground/test_grass2.png";
	}
	if (ground_type != 1) {

		int hoge = 1;
	}
	
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create(image_pass);

	sprite_data->setPosition((float)(MAP_BLOCK_WIDTH / 2), (float)(MAP_BLOCK_HEIGHT/2));
	this->addChild(sprite_data);
	this->_draw_x = block_x * MAP_BLOCK_WIDTH;
	this->_draw_y = block_y * MAP_BLOCK_HEIGHT;
	this->setPosition( (float)this->_draw_x,(float)this->_draw_y);
}