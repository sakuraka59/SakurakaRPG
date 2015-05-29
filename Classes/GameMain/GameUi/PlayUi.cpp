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
		this->_map_obj->setCharaPoint(npc_obj);

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
//	if (SET_VIEW_STATE == 1) {
		this->_map_obj->Update();
//	}
	
	/*
	for (std::unordered_map<int, MapObjectList*>::iterator map_obj_iterator = this->_map_obj_line_list.begin(); map_obj_iterator != this->_map_obj_line_list.end(); map_obj_iterator++) {
//		std::pair<int, MapObjectList*> map_obj_line = *map_obj_iterator;
//		this->_map_obj_line_list[map_obj_iterator->first]->Update();
//		map_obj_line;
		
	}
	// */
	/*
	foreach(KeyValuePair<int, Dictionary<int, MapObjectBase>> list_pair in this._map_obj_list) {
		foreach(KeyValuePair<int, MapObjectBase> pair in list_pair.Value) {
			pair.Value.Update();
		}
	}
	*/
	// �L�����N�^�[�̃A�b�v�f�[�g����
	for (std::list<CharaBase*>::iterator chara_iterator = this->_chara_list.begin(); chara_iterator != this->_chara_list.end(); chara_iterator++) {
		CharaBase* chara_obj = *chara_iterator;
		chara_obj->Update();
		// �}�b�v�I�u�W�F�N�g�Ƃ̓����蔻��
		this->checkHitMapObject(chara_obj);
	}

	// ���@�X�V

	// �X�L�������蔻��

	this->_player_obj->updateCamera();
	this->_play_camera->Update();

	// �L�����N�^�[�X�V
	for (std::list<CharaBase*>::iterator chara_iterator = this->_chara_list.begin(); chara_iterator != this->_chara_list.end(); chara_iterator++) {
		CharaBase* chara_obj = *chara_iterator;
		this->_order_object_list->reorderChild(chara_obj, (int)chara_obj->getDrawY() * (-1));
		chara_obj->updateDraw();
	}


	// ���@�̍X�V���� -----------------------------------------
	list<MagicBase*> delete_magic_list;

	for(MagicBase* magic_obj : this->_magic_list) {
		//Debug.WriteLine("[PlayUI]test:"+ hoge);
		if (magic_obj->getOrderSetFlag() == false) {
			this->_order_object_list->addChild(magic_obj, (int)magic_obj->getDrawY() * (-1));
			magic_obj->setOrderSetFlag();
		}

		magic_obj->Update();
		if (magic_obj->getRemoveFlag() == true) {


			// ���[�v���Ō����X�g����폜����ƃG���[��������̂ŁA�폜�����͕ʂɍs��
			delete_magic_list.push_back(magic_obj);
			//					this._order_object_list.RemoveChild(magic_obj, true);
			//					this._magic_list.Remove(magic_obj);
		}
		else {
			this->_order_object_list->reorderChild(magic_obj, (int)magic_obj->getDrawY() * (-1));
			
			//this->checkHitMagic(magic_obj, delete_magic_list);
		}

	}
	// �폜���X�g�ɓ��������@���폜����
	/*
	foreach(MagicBase magic_obj in delete_magic_list) {
		this._order_object_list.RemoveChild(magic_obj, true);
		this._shadow_list.removeRenderObject(magic_obj);
		this._magic_list.Remove(magic_obj);
		//Debug.WriteLine("[PlayUI]delete_magle "+magic_obj.GetType());
	}
	*/

	// �e�`�悷��
	this->_shadow_list->Update();


	//
	float camera_set_x = this->_play_camera->getCameraX();
	float camera_set_y = this->_play_camera->getCameraY();
	this->setPosition(camera_set_x, camera_set_y);
}
void PlayUi::checkHitMapObject(CharaBase* chara_obj) {

	return;
	//			if (chara_obj.getDrawX() != chara_obj.getBeforeX() ||
	//			    chara_obj.getDrawY() != chara_obj.getBeforeY()) {
	
	int chara_map_x = chara_obj->getMapBlockX();
	int chara_map_y = chara_obj->getMapBlockY();

	//			HitCheck hit_check_obj = new HitCheck();
	//			Debug.WriteLine("chara point:"+ chara_map_x+"/"+chara_map_y);


	for (int y = -1; y < 3; y++) {
		int check_map_y = chara_map_y + y;

		
		if (this->_map_obj_line_list[check_map_y] == nullptr) {
			continue;
		}
		
		for (int x = -1; x < 3; x++) {
			int check_map_x = chara_map_x + x;

			//							MapObjectBase check_map_obj = this._map_obj_line_list.getMapObject(check_map_x);
			MapObjectBase* check_map_obj = this->_map_obj_line_list[check_map_y]->getMapObject(check_map_x);
			if (check_map_obj == nullptr) {
				//								Debug.WriteLine("[PlayUI]hit check "+check_map_x+":"+check_map_y);
				continue;
			}

			
			HitCircle* circle_obj = chara_obj->getHitCircle();
			//*
			if (check_map_obj->getHitCheckType() == 3) {

				HitSquare* square_obj = check_map_obj->getHitSquare();
				//HitCheck.checkRectAndCircle(circle_obj, square_obj);
				//Debug.WriteLine("["+this.GetType()+"]check_chara:"+circle_obj.getRadius());


				if (HitCheck::checkRectAndCircle(circle_obj, square_obj) == true) {
					// �K���ɖ߂�
					chara_obj->setBeforeInsertDraw();
				}
			}
			//*/
		}
	}

	
	//			Debug.WriteLine("------------------");
	//			} else {
	//				Debug.WriteLine("before no");
	//			}

	//now_block_x = chara_obj._draw_x/ GameSetting._MAP_BLOCK_WIDTH;

}
CharaPlayer* PlayUi::getCharaPlayerObj() {
	return this->_player_obj;
}