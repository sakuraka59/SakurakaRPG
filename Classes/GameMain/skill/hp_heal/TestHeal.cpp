#include "TestHeal.h"
#include "../../chara/CharaBase.h"
TestHeal::TestHeal(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : SkillMyself(use_chara_obj, all_chara_list) {
	// ‘•”õŽí§ŒÀ
	this->_main_weapon_list[weaponType::all_weapon] = weaponType::all_weapon;

}
void TestHeal::skillInit() {
	this->_use_chara_obj->setAttackFrame(40);
	this->_use_chara_obj->setSkillFrame(30);
	//			Debug.WriteLine("[TestHeal]set skill init");
}

void TestHeal::attackHitEffect(CharaBase* check_chara_obj) {
	check_chara_obj->healHp(1000);
	//			Debug.WriteLine("[TestHeal]attackHitEffect");
}