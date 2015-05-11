#include "cocos2d.h"
#include "../../ResourceManage.h"
#include "PlayUi.h"
//#include "../chara/chara_seed/SeedBase.h"

#include "../GameCamera.h"
#include "../chara/CharaPlayer.h"
#include "../shadow/ShadowObjectList.h"
#include "../skill/SkillList.h"

using namespace cocos2d;

PlayUi::PlayUi(PlayerCommentUI* comment_ui_obj, cocos2d::EventListenerKeyboard* KEYBORD_EVENT) {
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
	
	this->_chara_list.push_back(this->_player_obj);

	this->_order_object_list->addChild(this->_player_obj, (int)(this->_player_obj->getDrawY() * (-1)));

	this->addChild(this->_order_object_list);
}
void PlayUi::Update(){
	// �L�����N�^�[�̃A�b�v�f�[�g����
	for (std::list<CharaBase*>::iterator chara_iterator = this->_chara_list.begin(); chara_iterator != this->_chara_list.end(); chara_iterator++) {
		CharaBase* chara_data = *chara_iterator;
		chara_data->Update();
	}

	// ���@�X�V

	// �X�L�������蔻��

	this->_player_obj->updateCamera();
	this->_play_camera->Update();

	// �`��X�V
	for (std::list<CharaBase*>::iterator chara_iterator = this->_chara_list.begin(); chara_iterator != this->_chara_list.end(); chara_iterator++) {
		CharaBase* chara_data = *chara_iterator;
		chara_data->updateDraw();
	}
}