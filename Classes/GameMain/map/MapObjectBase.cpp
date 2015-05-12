#include "MapObjectBase.h"
#include "../GAME_SETTING.h"
#include "../hit/HitSquare.h"

MapObjectBase::MapObjectBase(int map_block_x, int map_block_y, GameCamera* camera_obj) {
	this->_draw_x = (map_block_x * MAP_BLOCK_WIDTH);
	this->_draw_y = (map_block_y * MAP_BLOCK_HEIGHT);

	double test_angle = 0;
	this->_hit_square_obj = new HitSquare(this->_draw_x, this->_draw_y, MAP_BLOCK_WIDTH, MAP_BLOCK_HEIGHT, test_angle);

	this->setPosition((float)(this->_draw_x), 0);


	this->test_particle = cocos2d::ParticleSystemQuad::create("particle/test_particle.plist");
	this->test_particle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);//ParticleSystem::PositionType::RELATIVE
	this->addChild(this->test_particle);
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