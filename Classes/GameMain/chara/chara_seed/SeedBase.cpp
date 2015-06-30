#include "SeedBase.h"
// #include PartSetBase.h
// #include EquipSprite.h
// #include StateList.h
#include "../CharaBase.h"

#include "../abnormal_state/StateList.h"
#include "PartBase.h"
#include "../charaActionType.h"
/*
class PartSetBase;
class EquipSprite;
class StateList;
class CharaBase;
*/
SeedBase::SeedBase(CharaBase* chara_obj) {

	this->_chara_obj = chara_obj;
	this->_angle_direction = partsAngleType::front;
	/*
	this._test_point = i;
	this._draw_x = (int)(this._test_point /20) * 40;
	this._draw_y = 70;// 544/2;
	this._draw_y += (this._test_point % 20) * 50;
	//this.Order = this._draw_y;
	// �摜�X�v���C�g�錾
	Bounds2 bounds = base_scene.Camera2D.CalcBounds();

	// �摜�\���T�C�Y
	Vector2i numcells = new Vector2i(10,0);
	Vector2 cellsize = bounds.Size / numcells.Vector2();
	*/
	// �摜�\�� -------------------
	/*
	// �ǂݍ���
	this._sprite_data = ResourceManage.getSpriteTile("/Application/res/Objects.png",7,3);

	// �X�v���C�g���ł̕\�����e�ݒ�
	this._sprite_data.TileIndex2D = new Vector2i(4,2);

	// �\����_�𒆉���
	this._sprite_data.CenterSprite();
	*/
	// �\���ʒu�̒���
	// Vita �𑜓x 960,544

//	this->_seed_state_list = new StateList();
}

void SeedBase::Update() {
	this->updateAngle();
}
void SeedBase::updateAngle() {

	int angle_direction_base = this->_chara_obj->getMoveAnagleDirection();
	partsAngleType angle_direction = partsAngleType::no_type;
	switch (angle_direction_base) {
	case 0:
		angle_direction = partsAngleType::right;
		break;
	case 45:
		angle_direction = partsAngleType::back_right;
		break;
	case 90:
		angle_direction = partsAngleType::back;
		break;
	case 135:
		angle_direction = partsAngleType::back_left;
		break;
	case 180:
		angle_direction = partsAngleType::left;
		break;
	case 225:
		angle_direction = partsAngleType::front_left;
		break;
	case 270:
		angle_direction = partsAngleType::front;
		break;
	case 315:
		angle_direction = partsAngleType::front_right;
		break;
	}
	if (this->_angle_direction == angle_direction) {
		return;
	}

	// ������ύX����
	this->_angle_direction = angle_direction;
	this->updateAngleDetail();
}
void SeedBase::updateAngleDetail() {}

void SeedBase::updateAnimation() {
	charaActionType action_type = this->_chara_obj->getActionType();

	// �s�����ς�����ꍇ
	if (this->_action_type_before != action_type) {
		// �A�j���[�V����������
		this->_anime_frame = 0;
	} else {
		this->_anime_frame++;
	}
	// �ڍ׏�����
	this->updateAnimationDetail();

	this->_action_type_before = action_type;
}
void SeedBase::updateAnimationDetail() {}
// �摜
void SeedBase::setSpriteData(std::string file_name, int x, int y) {

	this->_file_name = file_name;
	this->_file_x = x;
	this->_file_y = y;
	// �ǂݍ���
	//this._base_sprite_data = ResourceManage.getSpriteTile(fine_name,x,y);
}
double SeedBase::getHeight() {
	return this->_height;
}
double SeedBase::getWidthHalf() {
	return this->_width;
}
int SeedBase::getCorrectX(){
	return this->_draw_correct_x;
}
int SeedBase::getCorrectY(){
	return this->_draw_correct_y;
}
float SeedBase::getScalePer() {
	return this->_scale_per;
}
double SeedBase::getRunSpeed() {
	return this->_run_speed;
}
double SeedBase::getWalkSpeed() {
	return this->_walk_speed;
}

int SeedBase::getBaseHp() {
	return this->_base_hp;
}
int SeedBase::getBaseSp() {
	return this->_base_sp;
}
int SeedBase::getBaseCc() {
	return this->_base_cc;
}

StateList* SeedBase::getStateList(CharaBase* chara_obj) {
	this->_seed_state_list = new StateList(chara_obj);
	this->setStateList(chara_obj);
	return this->_seed_state_list;
}

void SeedBase::setStateList(CharaBase* chara_obj) {

}
// vision data ----------------------------------------------
double SeedBase::getVisionRange() {
	return this->_vision_range;
}
double SeedBase::getVisionAngle() {
	return this->_vision_angle;
}
double SeedBase::getUnvisionRange() {
	return this->_unvision_range;
}
// search list ----------------------------------------------
std::list<charaGroupList> SeedBase::getMyGroupList() {
	return this->_my_group_list;
}
std::list<charaGroupList> SeedBase::getFellowGroupList() {
	return this->_fellow_group_list;
}

std::list<charaGroupList> SeedBase::getTargetGroupList() {
	return this->_target_group_list;
}
