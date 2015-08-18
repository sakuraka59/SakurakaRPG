#include "TreeObjBase.h"

TreeObjBase::TreeObjBase(int map_block_x, int map_block_y, GameCamera* camera_obj) :
MapObjectBase(map_block_x, map_block_y, camera_obj) {


	// /*
	int sprite_one_width = 102;
	int sprite_one_height = 171;
	int sprite_x = sprite_one_width * 5;
	int sprite_y = sprite_one_height * 0;

	cocos2d::Rect clip_rect = cocos2d::Rect(sprite_x, sprite_y, sprite_one_width, sprite_one_height);
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create("img/map/test_objects.png", clip_rect);

	// /*
	int particle_width = 64;
	int particle_height = 64;
	sprite_data->setPosition((particle_width / 2), 75);
	sprite_data->setScaleY(1.1f);
	this->addChild(sprite_data);
	// */
}
