#include "HumanTest.h"
#include "../../PartBase.h"

using namespace cocos2d;


HumanTest::HumanTest()
{
	// /*
	this->_part_test = new PartBase("/img/avatar/test/test_yukari.png", 0, (78 / 2));
	

	this->setRotation(0.0f);

	float scale_per = 1.0f;
	this->setScale(scale_per, scale_per);
	this->setPosition(0, -5);
	
	this->addChild(this->_part_test);

	

	/*/
	auto hoge = cocos2d::Sprite::create("CloseNormal.png");;
	this->addChild(hoge);
	// */
}