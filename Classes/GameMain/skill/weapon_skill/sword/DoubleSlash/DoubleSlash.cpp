#include "DoubleSlash.h"
#include "../../../SkillMove.h"
#include "../../../SkillAttackGroup.h"
#include "../../../../chara/CharaBase.h"

#include "../../../../magic/normal/TestMagicShot.h"

#include "../../../../magic/effect/one_hand/slash/slash_template2/SlashTemplate2.h"
#include "../../../../magic/effect/one_hand/slash/slash_template3/SlashTemplate3.h"

DoubleSlash::DoubleSlash(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : SkillSwordBase(use_chara_obj, all_chara_list) {

	// NPC‚Å‚Ì”­“®ŽË’ö‹——£
	this->_npc_use_range = 30.0;

	// Á”ïSP
	this->_use_sp = 0;

	// Á”ïCC
	this->_use_cc = 1;

	// Šî–{UŒ‚”ÍˆÍ
	int attack_range = 70;

	this->_set_attack_frame = 70;
	this->_set_skill_frame = 50;

	// ‘•”õŽí§ŒÀ
	this->_main_weapon_list[weaponType::sword] = weaponType::sword;


	// ‹ó’†”­“®‰Â”\
	//			this._in_air_flag = true;

	//this._skill_attack_list 

	int attack_speed = 10;
	this->slashTemplate3(attack_range, attack_speed);

	this->setSkillAttackGroup(new SkillAttackGroup(10));
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(3, 0, 0, 0, 0, 0, 0);
	
	this->slashTemplate2(attack_range, attack_speed);

}
void DoubleSlash::attackUpdateEffect(){

	int attack_speed = 10;
	int attack_range = 70;

	if (this->_skill_attack_count == 0 && this->_attack_frame == 0) {
		this->_use_chara_obj->setMagicList(new SlashTemplate3(this->_use_chara_obj, attack_range, attack_speed), false);

	} else if (this->_attack_reset_count == 1 && this->_skill_attack_count == 11 && this->_attack_frame == 0) {
		this->_use_chara_obj->setMagicList(new SlashTemplate2(this->_use_chara_obj, attack_range, attack_speed), false);
	}

}
void DoubleSlash::attackHitEffect(CharaBase* check_chara_obj) {

//	check_chara_obj->setDamagePush(5.0, this->_use_chara_obj->getMoveAngle(), 10);
	if (this->_attack_reset_count == 1) {
		check_chara_obj->setJumpForcing(5.0);

	} else {
		check_chara_obj->setJumpForcing(2.0);

	}
	check_chara_obj->directDamageHp(100);


	//	this->_use_chara_obj->setDamagePush(1.0, this->_use_chara_obj->getMoveAngle(), 10);
	//	this->_use_chara_obj->setJumpForcing(6.0);

}