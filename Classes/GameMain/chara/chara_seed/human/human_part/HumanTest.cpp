#include "HumanTest.h"
#include "../../PartBase.h"
#include "../../../CharaBase.h"

using namespace cocos2d;


HumanTest::HumanTest(CharaBase* chara_obj) : PartSetBase(chara_obj)
{
	// /*
//	this->_part_test = new PartBase("/img/avatar/test/test_yukari.png", 0, (78 / 2));
	
	this->_parts_obj_list[partsAngleType::front] = new PartBase("/img/avatar/test/test_yukari_1.png", 0, (78 / 2));
	this->_parts_obj_list[partsAngleType::front_left] = new PartBase("/img/avatar/test/test_yukari_2.png", 0, (78 / 2));
	
	this->_parts_obj_list[partsAngleType::left] = new PartBase("/img/avatar/test/test_yukari_3.png", 0, (78 / 2));
	this->_parts_obj_list[partsAngleType::back_left] = new PartBase("/img/avatar/test/test_yukari_4.png", 0, (78 / 2));
	this->_parts_obj_list[partsAngleType::back] = new PartBase("/img/avatar/test/test_yukari_5.png", 0, (78 / 2));
	this->_parts_obj_list[partsAngleType::back_right] = new PartBase("/img/avatar/test/test_yukari_6.png", 0, (78 / 2));
	this->_parts_obj_list[partsAngleType::right] = new PartBase("/img/avatar/test/test_yukari_7.png", 0, (78 / 2));
	this->_parts_obj_list[partsAngleType::front_right] = new PartBase("/img/avatar/test/test_yukari_8.png", 0, (78 / 2));
	
	this->_parts_obj_list[partsAngleType::front_left]->setPosition(3, 0);
	this->_parts_obj_list[partsAngleType::left]->setPosition(3, 0);
	this->_parts_obj_list[partsAngleType::back_left]->setPosition(3, 0);
	this->_parts_obj_list[partsAngleType::back_right]->setPosition(-3, 0);
	this->_parts_obj_list[partsAngleType::right]->setPosition(-3, 0);
	this->_parts_obj_list[partsAngleType::front_right]->setPosition(-3, 0);

	this->setRotation(0.0f);

	float scale_per = 1.0f;
	this->setScale(scale_per, scale_per);
	this->setPosition(0, -5);
	
	this->addChild(this->_parts_obj_list[partsAngleType::front]);

	

	/*/
	auto hoge = cocos2d::Sprite::create("CloseNormal.png");;
	this->addChild(hoge);
	// */
}