#include "cocos2d.h"
#include "../../ResourceManage.h"
#include "PlayUi.h"

using namespace cocos2d;

PlayUi::PlayUi() {

	this->_test_sprite = Sprite::create("HelloWorld.png");
	this->addChild(this->_test_sprite);
//	this->_test_sprite = ResourceManage::getSprite("icon.png");


}
void PlayUi::Update(){

}