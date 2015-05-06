#include "cocos2d.h"
#include "../../ResourceManage.h"
#include "PlayUi.h"
//#include "../chara/chara_seed/SeedBase.h"

#include "../GameCamera.h"
#include "../chara/CharaPlayer.h"
#include "../shadow/ShadowObjectList.h"
#include "../skill/SkillList.h"

using namespace cocos2d;

PlayUi::PlayUi(PlayerCommentUI* comment_ui_obj) {
	// test ---------------------------------------------------------
	this->_test_sprite = Sprite::create("HelloWorld.png");
//	this->_test_sprite->setPosition(new Vec2(500,0));
	this->_test_sprite->setPosition(500, 0);
	this->addChild(this->_test_sprite);
//	this->_test_sprite = ResourceManage::getSprite("icon.png");

//	SeedBase* hoge = new SeedBase();
//	CharaBase* piyo = new CharaBase();
	// test end -----------------------------------------------------
	this->_order_object_list = new RenderObject();

	// �\���ꏊ�̃J�������
	this->_play_camera = new GameCamera();

	// �I�u�W�F�N�g�̉e���
	this->_shadow_list = new ShadowObjectList(this->_play_camera);

	// �X�L���I�u�W�F�N�g�̐錾
	this->_skill_list = new SkillList();

	this->_player_obj = new CharaPlayer(this->_play_camera, comment_ui_obj, this->_chara_list, this->_skill_list, this->_magic_list, this->_shadow_list);

	this->_order_object_list->addChild(this->_player_obj, (int)(this->_player_obj->getDrawY() * (-1)));

	this->addChild(this->_order_object_list);
}
void PlayUi::Update(){

}