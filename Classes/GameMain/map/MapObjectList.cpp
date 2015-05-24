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
	
	
	/*
	this->_draw_flag = true;
	this->addChild(this->_object_draw_list);
	//*/

	this->_draw_flag = false;
	this->removeChild(this->_object_draw_list, true);

	int set_x = (int)(0 + this->_draw_correction_x);
	int set_y = (int)(this->_draw_y - this->_draw_correction_y);
	this->setPosition(set_x, set_y);

	this->_before_x = this->_player_obj->getMapBlockX();
	this->_before_y = this->_player_obj->getMapBlockY();
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
	// /*
	if (this->_draw_flag == true) {
		this->_object_draw_list->addChild(map_obj);
		this->_map_obj_draw_list[map_block_x] = true;
	}
	// */
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
	int width_side = this->mapDrawWidth();
	int height_side = this->mapDrawHeight();


	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();

	// Y�}�X���W�ړ������ꍇ
	if (this->_before_y != player_map_y) {
		if (this->_before_y < player_map_y){
			// ��ֈړ�

			// �`��͈͊O�̏ꍇ�A�I�u�W�F�N�g�̕\����S�폜
			if (this->_map_block_y < player_map_y - height_side) {
				this->removeObjectDrawY(height_side);
			} else {
				// �`��͈͓��̏ꍇ
				this->resetObjectDrawY(width_side, height_side);
			}

		} else {
			// ���ֈړ�
			if (this->_map_block_y > player_map_y - height_side) {
				this->removeObjectDrawY(height_side);
			}
			else {
				// �`��͈͓��̏ꍇ
				this->resetObjectDrawY(width_side, height_side);
			}
		}

		this->_before_y = this->_player_obj->getMapBlockY();
	}

	// X�}�X���W�ړ������ꍇ
	if (this->_draw_flag == true) {
		if (this->_before_x != player_map_x) {

			if (this->_before_x < player_map_x){
				// �E�ֈړ�
				// ���g�̈ʒu����[�ׂ̗Ȃ̂Łu-1�v���K�v
				int remove_x = player_map_x - width_side -1;
				this->removeObjectDrawX(remove_x);


				// �E�ֈړ�
				int add_x = player_map_x + width_side;
				this->resetObjectDrawX(add_x);
			} else {
				// ���ֈړ�
				// ���g�̈ʒu����[�ׂ̗Ȃ̂Łu+1�v���K�v
				int remove_x = player_map_x + width_side + 1;
				this->removeObjectDrawX(remove_x);


				// �E�ֈړ�
				int add_x = player_map_x - width_side;
				this->resetObjectDrawX(add_x);
			}
			this->_before_x = this->_player_obj->getMapBlockX();
		}
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
	return;
}
//-------------------------------------------------------------------
//	�L�����N�^�[�����ʒu�ݒ��̊e��I�u�W�F�N�g�`��
//-------------------------------------------------------------------
void MapObjectList::mapSetDrawInit() {
	
	// �L�����N�^�[�̃}�X���W����[�܂ł̃}�X��
	int width_side = this->mapDrawWidth();
	int height_side = this->mapDrawHeight();

	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();
	if (this->_map_block_y < player_map_y - height_side ||
		this->_map_block_y > player_map_y + height_side) {

		return;
	}

	this->resetObjectDrawY(width_side, height_side);
}
//-------------------------------------------------------------------
//	�I�u�W�F�N�g�̕`��}�X�͈�
//-------------------------------------------------------------------
int MapObjectList::mapDrawWidth() {
	int draw_width = ceil(GAME_WIDTH / MAP_BLOCK_WIDTH) / 2;
	draw_width += 1;

//	draw_width -= 2;
	return draw_width;
}
//-------------------------------------------------------------------
//	�I�u�W�F�N�g�̕`��}�X�͈�
//-------------------------------------------------------------------
int MapObjectList::mapDrawHeight(){
	int draw_height = ceil(GAME_HEIGHT / MAP_BLOCK_HEIGHT) / 2;
	draw_height += 2;

//	draw_height -= 3;
	return draw_height;
}

//-------------------------------------------------------------------
//	Y�}�X���W�̕`��͈͊O�ł̔�\������
//-------------------------------------------------------------------
void MapObjectList::removeObjectDrawY(int height_side) {
	if (this->_draw_flag == false) {
		return;
	}
//	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();
	int check_y_min = player_map_y - height_side;
	int check_y_max = player_map_y + height_side;
	if (this->_map_block_y >= check_y_min && this->_map_block_y <= check_y_max) {
		return;
	}
	int random_map_width = RandomDungeonSetting::getDungeonWidth();
	for (int map_block_x = 0; map_block_x < random_map_width; map_block_x++) {
		/*
		MapObjectBase* check_map_obj = this->getMapObject(map_block_x);
		if (check_map_obj == nullptr) {
			continue;
		}
		// */
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
void MapObjectList::resetObjectDrawY(int width_side, int height_side) {
	
	
	if (this->_draw_flag == true) {
		return;
	}
	int random_map_width = RandomDungeonSetting::getDungeonWidth();

	int player_map_x = this->_player_obj->getMapBlockX();
	int player_map_y = this->_player_obj->getMapBlockY();

	int check_y_min = player_map_y - height_side;
	int check_y_max = player_map_y + height_side;
	if (this->_map_block_y < check_y_min || this->_map_block_y > check_y_max) {
		return;
	}

	for (int map_block_x = 0; map_block_x < random_map_width; map_block_x++) {
		MapObjectBase* check_map_obj = this->getMapObject(map_block_x);
		if (check_map_obj == nullptr) {
			continue;
		}
		int check_x_min = player_map_x - width_side;
		int check_x_max = player_map_x + width_side;
		if (map_block_x < check_x_min || map_block_x > check_x_max) {
			continue;
		}
		this->_object_draw_list->addChild(check_map_obj);
		this->_map_obj_draw_list[map_block_x] = true;

	}
	// ���g�̃I�u�W�F�N�g�̕\����\��
	this->addChild(this->_object_draw_list, true);
	this->_draw_flag = true;
}

//-------------------------------------------------------------------
//	X�}�X���W�̕`��͈͊O�ł̔�\������
//-------------------------------------------------------------------
void MapObjectList::removeObjectDrawX(int remove_x) {
	if (this->_draw_flag == false) {
		return;
	}

	MapObjectBase* check_map_obj = this->getMapObject(remove_x);
	if (check_map_obj == nullptr) {
		return;
	}
	this->_object_draw_list->removeChild(check_map_obj, true);
	this->_map_obj_draw_list[remove_x] = false;
}

//-------------------------------------------------------------------
//	X�}�X���W�̕`��͈͓��ւ̕\���ĊJ����
//-------------------------------------------------------------------
void MapObjectList::resetObjectDrawX(int reset_x) {
	if (this->_draw_flag == false) {
		return;
	}
	if (this->_map_obj_draw_list[reset_x] == true) {
		return;
	}

	MapObjectBase* check_map_obj = this->getMapObject(reset_x);
	if (check_map_obj == nullptr) {
		return;
	}
	
	this->_object_draw_list->addChild(check_map_obj, true);
	this->_map_obj_draw_list[reset_x] = true;
}
