#include "PartBase.h"


PartBase::PartBase(std::string file_name, float origin_x, float origin_y) {

	this->_part_sprite = cocos2d::Sprite::create(file_name);

	this->_part_sprite->setPosition(origin_x, origin_y);
	this->addChild(this->_part_sprite);
}