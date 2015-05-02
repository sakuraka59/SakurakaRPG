#include "SkillAttackData.h"

SkillAttackData::SkillAttackData(int type, float check_a1, float check_a2,
	float check_b1, float check_b2,
	float attack_height_base, float attack_height) {

	this->_skill_attack_type = type;
	this->_check_a_1 = check_a1;
	this->_check_a_2 = check_a2;
	this->_check_b_1 = check_b1;
	this->_check_b_2 = check_b2;
	this->_attack_height_base = attack_height_base;
	this->_attack_height = attack_height;
}
int SkillAttackData::getSkillType() {
	return this->_skill_attack_type;
}