#include "SkillBase.h"
#include "SkillMove.h"

#include "../chara/CharaBase.h"

SkillBase::SkillBase(CharaBase* use_chara_obj, std::list<CharaBase*>* all_chara_list) {
	this->_use_chara_obj = use_chara_obj;
	this->_all_chara_list = all_chara_list;
	this->_skill_attack_count = 0;
	/*
	if (this._in_air_flag == true || use_chara_obj.checkGroundFlag() == true) {
	this.skillInit();
	}
	*/


}
SkillBase::~SkillBase() {

	// @TODO �e��I�u�W�F�N�g�j���͌�ł����I
	/*
	if (this->_skill_move_max > 0) {
		for (int move_num = 0; move_num < this->_skill_move_max; move_num++){
			this->_skill_move_list[this->_skill_move_max];
		}
	}
	*/
}
void SkillBase::skillInit() {
	this->_skill_attack_count = 0;
	this->_skill_move_count = 0;
	this->_move_frame = 0;
	this->_attack_frame = 0;
	this->skillExtendInit();
}

// set skill data to override
void SkillBase::skillExtendInit() { // virtual

}

void SkillBase::setSkillAttackGroup(SkillAttackGroup* skill_attack_obj) {

	this->_skill_attack_list[this->_skill_attack_max] = skill_attack_obj;
	this->_skill_attack_max++;
}
void SkillBase::setSkillMove(SkillMove* skill_move_obj) {

	this->_skill_move_list[this->_skill_move_max] = skill_move_obj;
	this->_skill_move_max++;
}
void SkillBase::Update() {	//virtual
	
	if (this->_delete_flag == true) {
//Debug.WriteLine("skill to delete flag");
	}
	
	/* @TODO 
	if (this->_use_chara_obj->getAttackFrame() <= 0 || this->_delete_flag == true) {

		return;
	}
	*/
	bool check_attack_flag = this->updateSkillEffect();

	bool check_move_flag = this->updateSkillMove();

	// �ړ��ƍU���A�����I�������폜���邱��
	if (check_attack_flag == true && check_move_flag == true) {
		//	Debug.WriteLine("[SkillBase]check check_attack_flag:"+check_attack_flag);
		//	Debug.WriteLine("[SkillBase]check check_move_flag:"+check_move_flag);
		// delete this object

		this->setDeleteFlag();
	}


	if (this->_delete_flag == true) {
		// delete this object
		int hoge = 1;
	}

}

bool SkillBase::updateSkillEffect() {	//virtual 
	return false;
}

void SkillBase::attackHitEffect(CharaBase* check_chara_obj) {	//virtual

	//			check_chara_obj.directDamageHp(1);
}
// move chara to skill use
bool SkillBase::updateSkillMove() {
	//*

	if (this->_skill_move_count >= this->_skill_move_max) {
		return true;
	}


	if (this->_move_frame >= this->_skill_move_list[this->_skill_move_count]->getFrameNum()) {
		this->_skill_move_count++;
		this->_move_frame = 0;
	}
	if (this->_skill_move_count >= this->_skill_move_max) {
		return true;
	}

	this->moveCheck();
	this->_move_frame++;
	// */
	return false;
}
void SkillBase::moveCheck() {


	SkillMove* skill_move_obj = this->_skill_move_list[this->_skill_move_count];
	double base_jump_power = skill_move_obj->getJunpPower();
	double jump_power = 0;
	if (this->_move_frame == 0 && base_jump_power > 0) {
		jump_power = base_jump_power;
	}

	//@TODO 
	this->_use_chara_obj->updateSkillMove(skill_move_obj->getAddAngle(), skill_move_obj->getOneFrameSpeed(), jump_power);
}
// this object to delete 
void SkillBase::setDeleteFlag() {
	//			Debug.WriteLine("skill to setDeleteFlag");
	//			Debug.WriteLine("[SkillBase] setDeleteFlag "+this->GetType().FullName);

	this->_delete_flag = true;
	//this->_use_chara_obj
}
bool SkillBase::getDeleteFlag() {

	return this->_delete_flag;
}
bool SkillBase::getInAirFlag() {
	return this->_in_air_flag;
}
int SkillBase::getUseSp() {
	return this->_use_sp;
}
int SkillBase::getUseCc() {
	return this->_use_cc;
}
bool SkillBase::checkWeaponType() {
	//			weaponType main_weapon_type = this->_use_chara_obj.getMainWeaponType();
	//			Debug.WriteLine("[SkillBase] check weapon type:"+main_weapon_type);

	// ���C������`�F�b�N
	// list

	//if (this->_main_weapon_list[this->_use_chara_obj->getMainWeaponType()] != nullptr) {
	
	if (this->_main_weapon_list.find(weaponType::all_weapon) == this->_main_weapon_list.end() &&
		this->_main_weapon_list.find(this->_use_chara_obj->getMainWeaponType()) == this->_main_weapon_list.end()) {
		return false;
	}
	/*
	if (this->_main_weapon_list.Count > 0 &&
		this->_main_weapon_list.Contains(this->_use_chara_obj.getMainWeaponType()) == false &&
		this->_main_weapon_list.Contains(weaponType.all_weapon) == false) {
		return false;
	}

	// �T�u����`�F�b�N
	if (this->_sub_weapon_list.Count > 0 &&
		this->_sub_weapon_list.Contains(this->_use_chara_obj.getSubWeaponType()) == false &&
		this->_sub_weapon_list.Contains(weaponType.all_weapon) == false) {
		return false;
	}
	*/
	return true;
}
// �e�X�L�����Ƃɓ��ʂȔ�������������ꍇ�Ɏg�p����`�F�b�N�֐�
bool SkillBase::checkExtendSkillUse() { //virtual
	return true;
}
// �X�L���̘A���񐔃J�E���g��i�߂邩�ǂ���
bool SkillBase::getChainCountFlag(){
	return this->_chain_count_flag;
}