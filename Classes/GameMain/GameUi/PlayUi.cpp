#include "cocos2d.h"
#include "../../ResourceManage.h"
#include "PlayUi.h"
//#include "../chara/chara_seed/SeedBase.h"

#include "../GAME_SETTING.h"
#include "../GameCamera.h"
#include "../chara/CharaPlayer.h"
#include "../chara/CharaNpc.h"
#include "../shadow/ShadowObjectList.h"
#include "../skill/SkillList.h"
#include "../map/MapBase.h"
#include "../map/MapObjectList.h"
#include "../map/MapObjectBase.h"

#include "../magic/MagicBase.h"

#include "../hit/HitCheck.h"
#include "../hit/HitCircle.h"
#include "../hit/HitSquare.h"

using namespace std;
using namespace cocos2d;

PlayUi::PlayUi(PlayerCommentUI* comment_ui_obj) {
	// test ---------------------------------------------------------
//	this->_test_sprite = Sprite::create("HelloWorld.png");
//	this->_test_sprite->setPosition(new Vec2(500,0));
//	this->_test_sprite->setPosition(500, 200);
//	this->addChild(this->_test_sprite);
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
//	this->_skill_list = new SkillList();

	// �v���C���[�L�����N�^�[�̐錾
	this->_player_obj = new CharaPlayer(this->_play_camera, comment_ui_obj, &this->_chara_list, &this->_magic_list, this->_shadow_list);
	
	this->_chara_list.push_back(this->_player_obj);
	this->_shadow_list->setRenderObject(this->_player_obj);


	this->_order_object_list->addChild(this->_player_obj, (int)(this->_player_obj->getDrawY() * (-1)));

	//�}�b�v���̐錾
	//if (SET_VIEW_STATE == 1) {
	this->_map_obj = new MapBase(this->_play_camera, this->_player_obj);
	this->addChild(this->_map_obj);
	//}


	//if (SET_MAP_MODE == 1) {
	for (int i = 0; i < 1; i++){
		CharaNpc* npc_obj = new CharaNpc(400 + 50 * i, -100, this->_play_camera, &this->_chara_list, &this->_magic_list, this->_shadow_list);
			
		this->_npc_list.push_back(npc_obj);
		this->_chara_list.push_back(npc_obj);

		this->_shadow_list->setRenderObject(npc_obj);
		this->_map_obj->setCharaPoint(npc_obj, 3);

		this->_order_object_list->addChild(npc_obj, (int)(npc_obj->getDrawY() * (-1)));
	}
	//}


	// �e�͒n�ʂ̏�ŁA����order�؂�ւ���n�I�u�W�F�N�g�̉�
	this->addChild(this->_shadow_list);

	this->addChild(this->_order_object_list);

	// �e�X�g
	/*
	this->_map_obj_line_list[0] = new MapObjectList(0, this->_play_camera, this->_player_obj);

	this->_map_obj_line_list[0]->setObject(0);
	this->_order_object_list->addChild(this->_map_obj_line_list[0], this->_map_obj_line_list[0]->getDrawY());
	*/

	
	
	/*
	ParticleSystemQuad* particle = ParticleSystemQuad::create("particle/test_particle.plist");
	particle->setPosition(0, 0);
	this->addChild(particle);
	*/

	this->_map_obj->Init();

	this->_map_obj_line_list = this->_map_obj->getMapObjectLineList();
//	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {

	//for(auto pair:mp){

		//		std::pair<int, MapObjectList*> map_obj_line = *map_obj_iterator;
		//		this->_map_obj_line_list[map_obj_iterator->first]->Update();
		//		map_obj_line;
		//this->_order_object_list->addChild(this->_map_obj_line_list[map_obj_iterator->first], this->_map_obj_line_list[map_obj_iterator->first]->getDrawY() * (-1));
	for (auto map_obj_line : this->_map_obj_line_list) {
		this->_order_object_list->addChild(map_obj_line.second, map_obj_line.second->getDrawY() *(-1));
	}
}
void PlayUi::Update(){
	// �}�b�v�A�b�v�f�[�g����

	this->_map_obj->Update();



	// �L�����N�^�[�̃A�b�v�f�[�g����
	for (CharaBase* chara_obj : this->_chara_list) {
		chara_obj->Update();
		// �}�b�v�I�u�W�F�N�g�Ƃ̓����蔻��
		this->checkHitMapObject(chara_obj);
	}
	/*
	for (std::list<CharaBase*>::iterator chara_iterator = this->_chara_list.begin(); chara_iterator != this->_chara_list.end(); chara_iterator++) {
		CharaBase* chara_obj = *chara_iterator;
		chara_obj->Update();
		// �}�b�v�I�u�W�F�N�g�Ƃ̓����蔻��
		this->checkHitMapObject(chara_obj);
	}
	*/
	// ���@�X�V

	// �X�L�������蔻��

	this->_player_obj->updateCamera();
	this->_play_camera->Update();

	// �L�����N�^�[�`��X�V
	for (CharaBase* chara_obj : this->_chara_list) {
		this->_order_object_list->reorderChild(chara_obj, (int)chara_obj->getDrawY() * (-1));
		chara_obj->updateDraw();
	}
	/*
	for (std::list<CharaBase*>::iterator chara_iterator = this->_chara_list.begin(); chara_iterator != this->_chara_list.end(); chara_iterator++) {
		CharaBase* chara_obj = *chara_iterator;
		this->_order_object_list->reorderChild(chara_obj, (int)chara_obj->getDrawY() * (-1));
		chara_obj->updateDraw();
	}
	*/

	// ���@�̍X�V���� -----------------------------------------
	list<MagicBase*> delete_magic_list;

	for(MagicBase* magic_obj : this->_magic_list) {
		//Debug.WriteLine("[PlayUI]test:"+ hoge);
		if (magic_obj->getOrderSetFlag() == false) {
			this->_order_object_list->addChild(magic_obj, (int)magic_obj->getDrawY() * (-1));
			magic_obj->setOrderSetFlag();
		}

		magic_obj->Update();
		if (magic_obj->getShadowRemoveFlag() == true) {
			magic_obj->removeShadow(this->_shadow_list);
		}

		if (magic_obj->getRemoveFlag() == true) {

			// ���[�v���Ō����X�g����폜����ƃG���[��������̂ŁA�폜�����͕ʂɍs��
			delete_magic_list.push_back(magic_obj);

		} else {
			this->_order_object_list->reorderChild(magic_obj, (int)magic_obj->getDrawY() * (-1));
			
			this->checkHitMagic(magic_obj, &delete_magic_list);
		}

	}
	// �폜���X�g�ɓ��������@���폜����
	
	for(MagicBase* magic_obj : delete_magic_list) {

//		this->_shadow_list->removeRenderObject(magic_obj);
		this->_order_object_list->removeChild(magic_obj, true);
		this->_magic_list.remove(magic_obj);
		
	}


	// �e�`�悷��
	this->_shadow_list->Update();


	//
	float camera_set_x = this->_play_camera->getCameraX();
	float camera_set_y = this->_play_camera->getCameraY();
	this->setPosition(camera_set_x, camera_set_y);
}
void PlayUi::checkHitMapObject(CharaBase* chara_obj) {

//	return;

	int chara_map_x = chara_obj->getMapBlockX();
	int chara_map_y = chara_obj->getMapBlockY();

	for (int y = -1; y < 3; y++) {
		int check_map_y = chara_map_y + y;

		
		if (this->_map_obj_line_list[check_map_y] == nullptr) {
			continue;
		}
		
		for (int x = -1; x < 3; x++) {
			int check_map_x = chara_map_x + x;

			MapObjectBase* check_map_obj = this->_map_obj_line_list[check_map_y]->getMapObject(check_map_x);
			if (check_map_obj == nullptr) {
				continue;
			}

			
			HitCircle* circle_obj = chara_obj->getHitCircle();

			if (check_map_obj->getHitCheckType() == 3) {

				HitSquare* square_obj = check_map_obj->getHitSquare();

				if (HitCheck::checkRectAndCircle(circle_obj, square_obj) == true) {
					// �K���ɖ߂�
					chara_obj->setBeforeInsertDraw();
				}
			}
		}
	}
}
void PlayUi::checkHitMagic(MagicBase* magic_obj, std::list<MagicBase*>* delete_magic_list) {
	int main_obj_map_x = magic_obj->getMapBlockX();
	int main_obj_map_y = magic_obj->getMapBlockY();
	HitCircle* circle_obj = magic_obj->getHitCircle();

	// �L�����N�^�[�Ƃ̓����蔻��
	for(CharaBase* chara_obj : this->_chara_list) {
		// �������{�l�͓�����Ȃ�
		if (magic_obj->getCharaObj() == chara_obj) {
			continue;
		}

		// �|�����G�ɂ͓�����Ȃ�
		if (chara_obj->getDownFlag() == true) {
			continue;
		}
		if (HitCheck::checkCircleAndCircle(circle_obj, chara_obj->getHitCircle()) == true &&
			this->checkHeightHit(magic_obj, chara_obj) == true) {
			// �����������肠��
			magic_obj->hitCharaDamage(chara_obj);
			delete_magic_list->push_back(magic_obj);
		}
	}

	// �I�u�W�F�N�g�Ƃ̓����蔻�� ----------------------------------------
	for (int y = -1; y < 3; y++) {
		int check_map_y = main_obj_map_y + y;

		if (this->_map_obj_line_list[check_map_y] == nullptr) {
			continue;
		}
		for (int x = -1; x < 3; x++) {
			int check_map_x = main_obj_map_x + x;

			MapObjectBase* check_map_obj = this->_map_obj_line_list[check_map_y]->getMapObject(check_map_x);
			if (check_map_obj == nullptr) {
				continue;
			}


			HitSquare* square_obj = check_map_obj->getHitSquare();

			HitCheck::checkRectAndCircle(circle_obj, square_obj);
			// �Ƃ肠�����K���ɔ��������

			//Debug.WriteLine("["+this.GetType()+"]check_magic:"+circle_obj.getRadius());
			if (check_map_obj->getHitCheckType() == 3) {

				if (HitCheck::checkRectAndCircle(circle_obj, square_obj) == true) {
					// �����������肠��
					magic_obj->removeShadow(this->_shadow_list);
					//delete_magic_list->push_back(magic_obj);
				}
			}

		}
	}

}
bool PlayUi::checkHeightHit(MagicBase* magic_obj, CharaBase* check_chara_obj) {

	double hit_height_base = (double)(magic_obj->getDrawZ());
	double hit_height_top = (double)(hit_height_base + magic_obj->getHitHeight());
	double chara_height_base = (double)(check_chara_obj->getDrawZ());
	double chara_height_top = (double)(check_chara_obj->getDrawZ() + check_chara_obj->getHitHeight());

	if (hit_height_top >= chara_height_base &&
		hit_height_base <= chara_height_top) {

		return true;
	}
	return false;
}
CharaPlayer* PlayUi::getCharaPlayerObj() {
	return this->_player_obj;
}