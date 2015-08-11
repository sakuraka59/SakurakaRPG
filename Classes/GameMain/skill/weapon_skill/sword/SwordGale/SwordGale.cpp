#include "SwordGale.h"
#include "../../../SkillMove.h"
#include "../../../SkillAttackGroup.h"
#include "../../../../chara/CharaBase.h"

#include "../../../../magic/normal/TestMagicShot.h"

SwordGale::SwordGale(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : SkillSwordBase(use_chara_obj, all_chara_list) {

	// NPC�ł̔����˒�����
	this->_npc_use_range = 30.0;

	// ����SP
	this->_use_sp = 0;

	// ����CC
	this->_use_cc = 2;

	// ��{�U���͈�
	int attack_range = 50;

	this->_set_attack_frame = 50;
	this->_set_skill_frame = 20;

	// �����퐧��
	this->_main_weapon_list[weaponType::sword] = weaponType::sword;
	

	// �󒆔����\
	//			this._in_air_flag = true;

	//this._skill_attack_list 

	int attack_speed = 1;

	SkillMove* move_base = new SkillMove(0, 0.25, 0, attack_speed);

	for (int i = 0; i < 10; i++) {
		int attack_angle_sad = i * 10;
		this->setSkillAttackGroup(new SkillAttackGroup(attack_speed));
		this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, (-60 + attack_angle_sad), (-30 + attack_angle_sad), 0, attack_range, 10, 10);
		this->setSkillMove(move_base);
	}


}
void SwordGale::attackUpdateEffect(){

	if (this->_skill_attack_count == 3 && this->_attack_frame == 0) {
		this->_use_chara_obj->setMagicList(new TestMagicShot(this->_use_chara_obj));
	}

}
void SwordGale::attackHitEffect(CharaBase* check_chara_obj) {

	check_chara_obj->setDamagePush(10.0, this->_use_chara_obj->getMoveAngle(), 10);
	check_chara_obj->setJumpForcing(2.0);
	check_chara_obj->directDamageHp(100);


//	this->_use_chara_obj->setDamagePush(1.0, this->_use_chara_obj->getMoveAngle(), 10);
//	this->_use_chara_obj->setJumpForcing(6.0);

}