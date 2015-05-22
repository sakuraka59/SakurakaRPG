#include "cocos2d.h"
#include "../GAME_SETTING.h"
#include "MapObjectList.h"
#include "MapObjectBase.h"
#include "../GameCamera.h"
#include "RandomDungeonSetting.h"
#include "../chara/CharaPlayer.h"
#include "../../Random.h"


MapObjectList::MapObjectList(int map_block_y, GameCamera* camera_obj, CharaPlayer* player_obj)
{
	this->_player_obj = player_obj;
	this->_camera_obj = camera_obj;
	//this->_texture_info = texture_info;

	//this->_object_sprite_list = new SpriteList(this->_texture_info);
//	this->_draw_correction_x = (MAP_BLOCK_WIDTH - this->_OBJECT_WIDTH) / 2;
	this->_object_draw_list = new RenderObject();

	this->_map_block_y = map_block_y;
	this->_draw_y = (map_block_y * MAP_BLOCK_HEIGHT);
	int hoge = 0;
	this->addChild(this->_object_draw_list);


	int set_x = (int)(0 + this->_draw_correction_x);
	int set_y = (int)(this->_draw_y - this->_draw_correction_y);
	this->setPosition(set_x, set_y);
	/*
	cocos2d::ParticleSystemQuad* particle = cocos2d::ParticleSystemQuad::create("particle/test_particle.plist");
	particle->setPosition(0, 0);
	this->addChild(particle);
	// */

}

void MapObjectList::setObject(int map_block_x){

	/*
	MapObjectBase map_obj = new MapObjectBase(
		this._texture_info,
		new Vector2i(5, 2),
		map_block_x, this._map_block_y
		, this._camera_obj
		);
	*/
	//			map_obj.Update();
	//			this._object_draw_list.AddChild(map_obj.getObjectSprite());

	MapObjectBase* map_obj = new MapObjectBase(
		map_block_x, this->_map_block_y
		, this->_camera_obj
		);
	this->_map_obj_line_list[map_block_x] = map_obj;
	this->_map_obj_draw_list[map_block_x] = false;

	// @TODO �Ƃ肠�����S�I�u�W�F�N�g��`�悷��
	this->_object_draw_list->addChild(map_obj);
	//this->addChild(map_obj);
	this->_map_obj_draw_list[map_block_x] = true;
}
bool MapObjectList::checkMapObject(int map_block_x) {
	//this._map_obj_line_list[map_block_x];	

	
	if (this->_map_obj_line_list[map_block_x] == nullptr) {
		return false;
	}
	
	return true;
}
MapObjectBase* MapObjectList::getMapObject(int map_block_x) {
	if (this->checkMapObject(map_block_x) == false) {
		return nullptr;
	}
	return this->_map_obj_line_list[map_block_x];

}
void MapObjectList::Update() {

	
	//---------------------------------------------------------------
	//	2015-05-22 �C����
	//	1�FX���W�AY���W���ړ����Ă����ꍇ �� X�u���b�N�AY�u���b�N���ړ����Ă����ꍇ�ɕύX
	//
	//	�EY���W�ړ���
	//		1�F���g�iMapobjectLine)����\���ɂȂ����ꍇ�A�q�v�f�����ׂ�Remove
	//		2�F���g���\���ɂȂ����ꍇ�A��_�i�v���C���[�L�����N�^�[�j����̎q�v�f�̂�Add
	//	�EX���W�ړ���
	//		1�F�����������g����\���̏ꍇ�A�������Ȃ�
	//		2�F�u���b�N���ړ����Ȃ�����A�������Ȃ�
	//		3�F�`��͈͓��ɓ������ꍇ��Add
	//		4�F�`��͈͊O�ɂȂ����ꍇ�ARemove
	//---------------------------------------------------------------

	// �L�����N�^�[�̃}�X���W����[�܂ł̃}�X��
	int width_side = 1;
	int height_side = 1;

	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();
	

	// Y�}�X���W�ړ������ꍇ
	if (this->_before_y != player_map_y) {
		if (this->_before_y < player_map_y){
			// ��ֈړ�

			// �`��͈͊O�̏ꍇ�A�I�u�W�F�N�g�̕\����S�폜
			if (this->_map_block_y < player_map_y - height_side) {
				this->removeLineObjectDraw();
			} else {
				// �`��͈͓��̏ꍇ
				this->resetLineObjectDraw(player_map_y, width_side);
			}

		} else {
			// ���ֈړ�

		}

	}

	this->_before_x = this->_player_obj->getMapBlockX();
	this->_before_y = this->_player_obj->getMapBlockY();
	return;
	/*
	int set_x = (int)(0 + this->_draw_correction_x);
	int set_y = (int)(this->_draw_y - this->_draw_correction_y);

//	int set_x = (int)(0 - this->_camera_obj->getCameraX() + this->_draw_correction_x);
//	int set_y = (int)(this->_draw_y - this->_camera_obj->getCameraY() - this->_draw_correction_y);

	// �J�������������ꍇ�̂�
	if (set_x != this->_before_x || set_y != this->_before_y) {
		//this->Position = new Vector2(set_x, set_y);
		this->setPosition(set_x, set_y);

		// /*
		
		Random* rand_obj = new Random();

		this->_before_x = set_x;
		this->_before_y = set_y;

		int player_map_y = this->_player_obj->getMapBlockY();

		int obj_draw_width = (int)ceil((double)GAME_WIDTH / (double)MAP_BLOCK_WIDTH); +1;
		int obj_draw_height = (int)ceil((double)GAME_HEIGHT / (double)MAP_BLOCK_HEIGHT); ;
		bool draw_change_flag = false;
		
		// ���C����̃I�u�W�F�N�g���\���ɂ���
		if (this->_draw_flag == true) {
			if (this->_map_block_y + obj_draw_height < player_map_y ||
				this->_map_block_y - obj_draw_height > player_map_y) {

				this->removeChild(this->_object_draw_list, true);
				this->_draw_flag = false;

				draw_change_flag = true;
			}
		} else {
			if (this->_map_block_y + obj_draw_height >= player_map_y &&
				this->_map_block_y - obj_draw_height <= player_map_y) {
				this->addChild(this->_object_draw_list);
				this->_draw_flag = true;

				draw_change_flag = true;
			}
		}
		
		// x -----------------------------
		//*
		int player_map_x = this->_player_obj->getMapBlockX();
		int check_x_width = (obj_draw_width + 1);
		for (int check_obj_x = 0; check_obj_x < (check_x_width * 2 + 1); check_obj_x++){

			int check_map_x = player_map_x - check_x_width + check_obj_x;
			MapObjectBase* check_map_obj = this->getMapObject(check_map_x);
			if (check_map_obj == nullptr) {
				continue;
			}
			//	Debug.WriteLine("[MapObjectList]rand : "+rand_obj.Next(1000000));
			//	Debug.WriteLine("[MapObjectList]check_obj_x : "+check_obj_x+"_map_block_y : "+this->_map_block_y);

			if (check_map_x + obj_draw_width < player_map_x ||
				check_map_x - obj_draw_width > player_map_x) {

				if (this->_map_obj_draw_list[check_map_x] == true) {

					this->_object_draw_list->removeChild(check_map_obj, true);

					this->_map_obj_draw_list[check_map_x] = false;
				}
				//						check_map_obj.removeDrawObject();

			}
			else if (check_map_x + obj_draw_width >= player_map_x &&
				check_map_x - obj_draw_width <= player_map_x) {
				if (this->_map_obj_draw_list[check_map_x] == false) {

					this->_object_draw_list->addChild(check_map_obj);

					this->_map_obj_draw_list[check_map_x] = true;
				}
				//						this->_object_sprite_list.AddChild(check_map_obj.getObjectSprite());
				//						check_map_obj.resetDrawObject();

			}
			
		}
		//	this->_map_obj_line_list[map_block_x]
		
		delete rand_obj;
		
	}



	// �e�I�u�W�F�N�g�A�j���[�V����
	int draw_block_width = RandomDungeonSetting::getDungeonWidth();
//	int draw_block_width = (int)ceil((double)GAME_WIDTH / (double)MAP_BLOCK_WIDTH);
	if (this->_draw_flag == true) {
		for (int map_x = 0; map_x < draw_block_width; map_x++) {

			if (this->_map_obj_line_list[map_x] != nullptr  &&
				this->_map_obj_draw_list[map_x] == true) {

				this->_map_obj_line_list[map_x]->Update();
			}
		}
	}
	// */
}
//-------------------------------------------------------------------
//	Y�}�X���W�̕`��͈͊O�ł̔�\������
//-------------------------------------------------------------------
void MapObjectList::removeLineObjectDraw() {
	if (this->_draw_flag == false) {
		return;
	}
	int random_map_width = RandomDungeonSetting::getDungeonWidth();
	for (int map_block_x = 0; map_block_x < random_map_width; map_block_x++) {
		MapObjectBase* check_map_obj = this->getMapObject(map_block_x);
		if (check_map_obj == nullptr) {
			continue;
		}
		this->_map_obj_draw_list[map_block_x] = false;
	}
	this->_object_draw_list->removeAllChildren();
	// ���g�̃I�u�W�F�N�g�̕\����S�폜
	this->removeChild(this->_object_draw_list, true);
	this->_draw_flag = false;
}
//-------------------------------------------------------------------
//	Y�}�X���W�̕`��͈͓��ւ̕\���ĊJ����
//-------------------------------------------------------------------
void MapObjectList::resetLineObjectDraw(int player_map_x, int width_side) {
	return;
	int random_map_width = RandomDungeonSetting::getDungeonWidth();
	for (int map_block_x = 0; map_block_x < random_map_width; map_block_x++) {
		MapObjectBase* check_map_obj = this->getMapObject(map_block_x);
		if (check_map_obj == nullptr) {
			continue;
		}

		if (map_block_x < player_map_x - width_side || map_block_x > player_map_x + width_side) {
			continue;
		}
		this->_object_draw_list->addChild(check_map_obj);
		this->_map_obj_draw_list[map_block_x] = true;

	}
	// ���g�̃I�u�W�F�N�g�̕\����\��
	this->addChild(this->_object_draw_list, true);
	this->_draw_flag = true;
}