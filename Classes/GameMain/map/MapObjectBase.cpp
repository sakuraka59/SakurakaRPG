#include "MapObjectBase.h"
#include "../GAME_SETTING.h"
#include "../hit/HitSquare.h"
#include "../../Random.h"

MapObjectBase::MapObjectBase(int map_block_x, int map_block_y, GameCamera* camera_obj) {
	this->_draw_x = (map_block_x * MAP_BLOCK_WIDTH);
	this->_draw_y = (map_block_y * MAP_BLOCK_HEIGHT);

	double test_angle = 0;
	this->_hit_square_obj = new HitSquare(this->_draw_x, this->_draw_y, MAP_BLOCK_WIDTH, MAP_BLOCK_HEIGHT, test_angle);


	this->setPosition((float)(this->_draw_x), 0);
	// /*
	int sprite_one_width = 102;
	int sprite_one_height = 171;
	int sprite_x = sprite_one_width * 5;
	int sprite_y = sprite_one_height * 0;

	cocos2d::Rect clip_rect = cocos2d::Rect(sprite_x, sprite_y, sprite_one_width, sprite_one_height);
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create("img/map/test_objects.png", clip_rect);
	

	int particle_width = 64;
	int particle_height = 64;
	sprite_data->setPosition((particle_width / 2), 75);
	sprite_data->setScaleY(1.1f);
	this->addChild(sprite_data);
	// */
	 /*
	// test sprite object
	this->test_particle = cocos2d::ParticleSystemQuad::create("particle/test_obj2.plist");
	this->test_particle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);//ParticleSystem::PositionType::RELATIVE
//	cocos2d::Size imgSize = this->test_particle->getContentSize();
	int particle_width = 64;
	int particle_height = 64;
	this->test_particle->setPosition((particle_width / 2), (particle_height / 2));

	this->addChild(this->test_particle);


	// */
}
void MapObjectBase::Update() {
	//test anime
	Random* random_obj = new Random();

	double anime_move_base = 0.01;
	if (this->_anime_num >= 0) {
		this->_anime_move_speed -= (anime_move_base + (anime_move_base * (random_obj->getRandNum(100) / 100)));
	} else {
		this->_anime_move_speed += (anime_move_base + (anime_move_base * (random_obj->getRandNum(100) / 100)));
	}
	this->_anime_num += this->_anime_move_speed;
	this->setRotationX(this->_anime_num);
	/*
	double anime_move = 0.2;
	double anime_max = 5;
	if (this->anime_statue == 0) {
		this->anime_num += anime_move;
		if (this->anime_num >= anime_max) {
			this->anime_statue = 1;
		}
	} else {
		this->anime_num -= anime_move;
		if (this->anime_num <= anime_max *(-1)) {
			this->anime_statue = 0;
		}
	}
	this->setRotationX((int)this->anime_num);
	//this->setPosition((float)(this->_draw_x), 0);
	*/

	delete random_obj;
}
int MapObjectBase::getHitCheckType() {
	return this->_hit_check_type;
}
HitSquare* MapObjectBase::getHitSquare() {
	return this->_hit_square_obj;
}


void MapObjectBase::resetDrawObject() {
	if (this->_DRAW_FLAG == false) {
		this->_DRAW_FLAG = true;
		//	Debug.WriteLine("[MapObjectBase]add child");		
		//				this.AddChild(this._object_sprite);
	}
}
void MapObjectBase::removeDrawObject() {
	if (this->_DRAW_FLAG == true) {
		this->_DRAW_FLAG = false;
		//	Debug.WriteLine("[MapObjectBase]remove child");
		//				this.RemoveChild(this._object_sprite, true);
	}
}