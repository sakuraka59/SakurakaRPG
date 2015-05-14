#include "MapGroundBase.h"

#include "cocos2d.h"
#include "../GAME_SETTING.h"


MapGroundBase::MapGroundBase(int block_x, int block_y, int map_width, int map_height, int test_type) {

//	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create("/img/map/maptest2.png");

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
	switch (test_type) {
	case 1:
		// ƒfƒtƒHƒ‹ƒg•Ç
		sprite_data->setColor(cocos2d::Color3B(0, 255, 0));
		break;
	case 2:
		// •”‰®
		sprite_data->setColor(cocos2d::Color3B(112, 146, 190));
		break;
	case 3:
		// ’Ê˜H
		sprite_data->setColor(cocos2d::Color3B(185, 122, 87));
		break;
	case 4:
		// ’Ê˜HÚ‘±
		sprite_data->setColor(cocos2d::Color3B(0, 162, 232));
		break;
	case 5:
		// ‹­§•Ç
		sprite_data->setColor(cocos2d::Color3B(255, 0, 0));
		break;
	case 6:
		
		sprite_data->setColor(cocos2d::Color3B(255, 242, 0));
		break;
	default:
		sprite_data->setColor(cocos2d::Color3B(0, 0, 0));
		break;
	}
	this->addChild(sprite_data);
	this->_draw_x = block_x * MAP_BLOCK_WIDTH;
	this->_draw_y = block_y * MAP_BLOCK_HEIGHT;
	this->setPosition( (float)this->_draw_x,(float)this->_draw_y);
}