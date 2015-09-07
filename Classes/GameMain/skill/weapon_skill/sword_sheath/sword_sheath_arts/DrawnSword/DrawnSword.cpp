#include "DrawnSword.h"
#include "../../../../SkillMove.h"
#include "../../../../SkillAttackGroup.h"
#include "../../../../../chara/CharaBase.h"

#include "../../../../../magic/normal/TestMagicShot.h"

#include "../../../../../magic/effect/one_hand/slash/slash_template2/SlashTemplate2.h"
#include "../../../../../magic/effect/one_hand/slash/slash_template3/SlashTemplate3.h"

DrawnSword::DrawnSword(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : SkillSwordSheathArtsBase(use_chara_obj, all_chara_list) {

	this->_skill_id = "DrawnSword";

	// リストに表示しない
	this->_ui_draw_flag = false;

	// NPCでの発動射程距離
	this->_npc_use_range = 30.0;

	// 消費SP
	this->_use_sp = 0;

	// 消費CC
	this->_use_cc = 1;

	// 基本攻撃範囲
	int attack_range = 70;

	this->_set_attack_frame = 50;
	this->_set_skill_frame = 30;

	// 装備種制限
	this->_main_weapon_list[weaponType::sword] = weaponType::sword;
	this->_sub_weapon_list[weaponType::sheath] = weaponType::sheath;


	// 空中発動可能
	//			this._in_air_flag = true;

	//this._skill_attack_list 

	int attack_speed = 1;
	this->slashTemplate3(attack_range, attack_speed);

	this->setSkillAttackGroup(new SkillAttackGroup(10));
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(3, 0, 0, 0, 0, 0, 0);

	this->slashTemplate2(attack_range, attack_speed);

}
void DrawnSword::skillInit(){
	SkillSwordSheathArtsBase::skillInit();
	this->_use_chara_obj->sendComment("一閃っ！");
	this->_use_chara_obj->setWeaponState(1);
}
void DrawnSword::attackUpdateEffect(){

	int attack_speed = 10;
	int attack_range = 70;

	if (this->_skill_attack_count == 0 && this->_attack_frame == 0) {
		this->_use_chara_obj->setMagicList(new SlashTemplate2(this->_use_chara_obj, attack_range, attack_speed), false);

	}
}
void DrawnSword::attackHitEffect(CharaBase* check_chara_obj) {

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