#include "SkillList.h"
#include <typeinfo>

#include "SkillBase.h"

#include "weapon_skill/sword/SwordGale/SwordGale.h"
#include "weapon_skill/sword/DoubleSlash/DoubleSlash.h"
#include "weapon_skill/sword_sheath/sword_sheath_arts/DrawnSword/DrawnSword.h"

#include "magic/normal/TestShot.h"
SkillList::SkillList(CharaBase* chara_obj, list<CharaBase*>* all_chara_list) {

	// 全スキル宣言をここで行う

	// 片手剣
	this->setSkillListInit(new SwordGale(chara_obj, all_chara_list), skillType::sword);
	this->setSkillListInit(new DoubleSlash(chara_obj, all_chara_list), skillType::sword);

	// 片手剣＋鞘
	this->setSkillListInit(new DrawnSword(chara_obj, all_chara_list), skillType::sword_sheath);

	// 魔法：無属性
	this->setSkillListInit(new TestShot(chara_obj, all_chara_list), skillType::magic_normal);
}
void SkillList::setSkillListInit(SkillBase* skill_obj, skillType skill_type) {
	
	string skill_id = skill_obj->getSkillId();

	this->_skill_list[skill_id] = skill_obj;
	this->_skill_type_list[skill_type][skill_id] = skill_obj;
}

SkillBase* SkillList::getSkillObj(string skill_id) {
	return this->_skill_list[skill_id];
}
map<string, SkillBase*> SkillList::getSkillObjList(skillType skill_type) {
	return this->_skill_type_list[skill_type];
}
map<skillType, map<string, SkillBase*>> SkillList::getSkillTypeObjList() {
	return this->_skill_type_list;
}