#include "PartSetBase.h"
#include "../CharaBase.h"
#include "PartBase.h"

PartSetBase::PartSetBase(CharaBase* chara_obj) {
	this->_chara_obj = chara_obj;
	this->_angle_direction = partsAngleType::no_type;
}
void PartSetBase::Update() {

}
void PartSetBase::updateAngle(partsAngleType angle_type) {
	this->removeAllChildren();
	this->addChild(this->_parts_obj_list[angle_type]);
}