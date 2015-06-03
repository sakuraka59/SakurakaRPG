#include "MapGroundBase.h"

#include "cocos2d.h"
#include "../GAME_SETTING.h"

#include "mapGroundType.h"

MapGroundBase::MapGroundBase(int block_x, int block_y, int ground_type) {

//	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create("/img/map/maptest2.png");
	/*
	cocos2d::Rect rect = cocos2d::Rect(0, 0, MAP_BLOCK_WIDTH, MAP_BLOCK_HEIGHT);
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create();
	sprite_data->setTextureRect(rect);


//	sprite_data->setScale((float)MAP_BLOCK_WIDTH, (float)MAP_BLOCK_HEIGHT);
	
//	sprite_data->setScale((float)MAP_BLOCK_WIDTH, (float)MAP_BLOCK_HEIGHT);
//	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create("HelloWorld.png");
	
	sprite_data->setPosition(32, 32);
	cocos2d::ccBlendFunc blend;
	blend.src = GL_SRC_ALPHA;
	blend.dst = GL_ONE;
	sprite_data->setBlendFunc((blend));
	switch (ground_type) {
	case 1:
		// デフォルト壁
		sprite_data->setColor(cocos2d::Color3B(0, 255, 0));
		break;
	case 2:
		// 部屋
		sprite_data->setColor(cocos2d::Color3B(112, 146, 190));
		break;
	case 3:
		// 通路
		sprite_data->setColor(cocos2d::Color3B(185, 122, 87));
		break;
	case 4:
		// 通路接続
		sprite_data->setColor(cocos2d::Color3B(0, 162, 232));
		break;
	case 5:
		// 強制壁
		sprite_data->setColor(cocos2d::Color3B(255, 0, 0));
		break;
	case 6:
		
		sprite_data->setColor(cocos2d::Color3B(255, 242, 0));
		break;
	default:
		sprite_data->setColor(cocos2d::Color3B(0, 0, 0));
		break;
	}
	*/
	std::string image_pass = "img/map/ground/test_grass.png";
	switch (ground_type) {
	case (int)mapGroundType::grass: //草地
		image_pass = "img/map/ground/test_grass1.png";
		break;
	case (int)mapGroundType::new_load: //古い道路
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