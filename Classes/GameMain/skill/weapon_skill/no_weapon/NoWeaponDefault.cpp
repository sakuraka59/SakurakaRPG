#include "NoWeaponDefault.h"
#include "../../SkillAttackGroup.h"
#include "../../SkillMove.h"
#include "../../../chara/abnormal_state/abnormalStateType.h"
#include "../../../chara/CharaBase.h"

NoWeaponDefault::NoWeaponDefault(CharaBase* use_chara_obj, std::list<CharaBase*> all_chara_list) : SkillAttack(use_chara_obj, all_chara_list) {
	//this->_skill_attack_list 
	this->_npc_use_range = 30.0;

	// dash panch
	this->setSkillAttackGroup(new SkillAttackGroup(5));
	this->setSkillMove(new SkillMove(0, 0, 0, 5));

	this->setSkillAttackGroup(new SkillAttackGroup(5));
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, -20, 20, 0, 50, 10, 10);
	this->setSkillMove(new SkillMove(0, 2.0, 0, 5));

	this->setSkillAttackGroup(new SkillAttackGroup(5));
	this->setSkillMove(new SkillMove(0, -2.0, 0, 5));


	// abnormal state
	this->_abnormal_state_type = abnormalStateType::poison;
	this->_state_level = 1;
	this->_state_rate = 2000;


}
// ユーザーの状態をセットする
void NoWeaponDefault::skillExtendInit() {

	this->_use_chara_obj->setAttackFrame(40);
	this->_use_chara_obj->setSkillFrame(30);


}

void NoWeaponDefault::attackHitEffect(CharaBase* check_chara_obj) {

	check_chara_obj->directDamageHp(100);
	check_chara_obj->checkToSetState(this->_abnormal_state_type, this->_state_level, this->_state_rate);

}