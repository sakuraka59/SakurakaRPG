#include "cocos2d.h"
#include "../../ResourceManage.h"
#include "PlayUi.h"
#include "../chara/chara_seed/SeedBase.h"
//#include "../chara/CharaBase.h"

using namespace cocos2d;

PlayUi::PlayUi() {

	this->_test_sprite = Sprite::create("HelloWorld.png");
	this->addChild(this->_test_sprite);
//	this->_test_sprite = ResourceManage::getSprite("icon.png");

//	SeedBase* hoge = new SeedBase();
//	CharaBase* piyo = new CharaBase();

}
void PlayUi::Update(){

}