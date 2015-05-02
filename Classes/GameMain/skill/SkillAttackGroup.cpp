#include "SkillAttackGroup.h"
#include "SkillAttackData.h"

SkillAttackGroup::SkillAttackGroup(int frame_num) {
	this->_frame_num = frame_num;
}
int SkillAttackGroup::getFrameNum() {
	return this->_frame_num;
}

void SkillAttackGroup::setSkillAttack(int type, float check_a1, float check_a2,
	float check_b1, float check_b2,
	float attack_height_base, float attack_height) {

	this->_attack_data_list[this->_list_num] = new SkillAttackData(type, check_a1, check_a2,
		check_b1, check_b2,
		attack_height_base, attack_height);

	this->_list_num++;
}
SkillAttackData* SkillAttackGroup::getSkillAttack(int index){
	return this->_attack_data_list[index];
}
int SkillAttackGroup::getSkillSize(){
	//return this->_attack_data_list.Size();
	return this->_list_num;
}