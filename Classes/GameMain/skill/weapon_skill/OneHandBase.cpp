#include "OneHandBase.h"
#include <math.h>

#include "../SkillMove.h"
#include "../SkillAttackGroup.h"

OneHandBase::OneHandBase(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : SkillAttack(use_chara_obj, all_chara_list) {
}

// �E�ォ�獶����
void OneHandBase::slashTemplate1(int attack_range, int attack_speed, SkillMove* set_move) {

	if (set_move == nullptr) {
		set_move = new SkillMove(0, 0, 0, attack_speed);
	}
	this->setSkillMove(set_move);

	int motion_min_angle = -80;
	int motion_max_angle = 80;
	int height_base_max = 20;

	int motion_sad_angle = (int)floor((double)(motion_max_angle - motion_min_angle) / attack_speed);
	//	Debug.WriteLine("[OneHandBase]check temp 1---------------------------------------------");
	for (int i = 0; i < attack_speed; i++) {

		int min_angle = (motion_min_angle + (motion_sad_angle * (i)));
		int max_angle = (motion_min_angle + (motion_sad_angle * (i + 1)));
		int height_base = height_base_max - ((int)ceil((double)height_base_max / attack_speed) * i);
		//int height_base = 20 - (i * 5);

		this->setSkillAttackGroup(new SkillAttackGroup(1));
		this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, min_angle, max_angle, 0, attack_range, height_base, 10);
	}
	/*
	SkillMove move_base = new SkillMove(0, 1.5, 0, attack_speed);

	for (int i = 0; i < 5; i++) {
	int attack_angle_sad = i * 30;
	this.setSkillAttackGroup(new SkillAttackGroup(attack_speed));

	int min_angle = (-90 + attack_angle_sad);
	int max_angle = (-60 + attack_angle_sad);
	int height_base = 20 - (i * 5);

	this._skill_attack_list[this._skill_attack_max -1].setSkillAttack(2, min_angle, max_angle, 0, attack_range, height_base, 10);
	this.setSkillMove(move_base);
	}
	*/
}
// �E�����獶��֐؂蕥��
void OneHandBase::slashTemplate2(int attack_range, int attack_speed, SkillMove* set_move) {

	if (set_move == nullptr) {
		set_move = new SkillMove(0, 0, 0, attack_speed);
	}
	this->setSkillMove(set_move);

	int motion_min_angle = -80;
	int motion_max_angle = 80;
	int height_base_max = 20;

	int motion_sad_angle = (int)floor((double)(motion_max_angle - motion_min_angle) / attack_speed);
	//	Debug.WriteLine("[OneHandBase]check temp 1---------------------------------------------");
	for (int i = 0; i < attack_speed; i++) {

		int min_angle = (motion_min_angle + (motion_sad_angle * (i)));
		int max_angle = (motion_min_angle + (motion_sad_angle * (i + 1)));
		int height_base = 0 + ((int)ceil((double)height_base_max / attack_speed) * i);
		//int height_base = 20 - (i * 5);

		this->setSkillAttackGroup(new SkillAttackGroup(1));
		this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, min_angle, max_angle, 0, attack_range, height_base, 10);
	}


}
// ���ォ��E���֐؂蕥��
void OneHandBase::slashTemplate3(int attack_range, int attack_speed, SkillMove* set_move) {

	// skillMove�������Ɠ����蔻�肪�d�����Ȃ��̂ŁA��f�[�^�ł��Z�b�g���邱��
	//SkillMove move_base = new SkillMove(0, 0, 0, attack_speed);
	if (set_move == nullptr) {
		set_move = new SkillMove(0, 0, 0, attack_speed);
	}
	this->setSkillMove(set_move);

	int motion_min_angle = -80;
	int motion_max_angle = 80;
	int height_base_max = 40;

	int motion_sad_angle = (int)floor((double)(motion_max_angle - motion_min_angle) / attack_speed);

	for (int i = 0; i < attack_speed; i++) {

		int min_angle = (motion_max_angle - (motion_sad_angle * (i + 1)));
		int max_angle = (motion_max_angle - (motion_sad_angle * (i)));
//		int height_base = 10; //+ (i * 1);
		int height_base = height_base_max - ((int)ceil((double)height_base_max / attack_speed) * i);
//		int height_base = 0 + ((int)ceil((double)height_base_max / attack_speed) * i);

		this->setSkillAttackGroup(new SkillAttackGroup(1));
		this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, min_angle, max_angle, 0, attack_range, height_base, 20);

	}
	/*
	SkillMove move_base = new SkillMove(0, 0.25, 0, attack_speed);
	//	Debug.WriteLine("[OneHandBase]check temp 3---------------------------------------------");
	for (int i = 0; i < 10; i++) {
	int attack_angle_sad = i * 10;
	this.setSkillAttackGroup(new SkillAttackGroup(attack_speed));

	int min_angle = (30 - attack_angle_sad);
	int max_angle = (60 - attack_angle_sad);
	int height_base = 15 - (i * 2);
	//	Debug.WriteLine("[OneHandBase]check:"+min_angle+"/"+max_angle);
	this._skill_attack_list[this._skill_attack_max -1].setSkillAttack(2, min_angle, max_angle, 0, attack_range, height_base, 10);
	this.setSkillMove(move_base);
	}
	*/
}
// �˂��U���n ----------------------------------------------------

// ���ʂ֓˂��U��
void OneHandBase::ThrustTemplate1(int attack_range, int attack_speed, int end_attack_frame, SkillMove* set_move) {

	double attack_range_set = ((double)attack_range / 3);


	this->setSkillAttackGroup(new SkillAttackGroup(attack_speed));
	if (set_move != nullptr) {
		this->setSkillMove(set_move);
	}
	int base_height = 10;
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, -30, 30, 0, (int)attack_range_set, base_height, 10);

	this->setSkillAttackGroup(new SkillAttackGroup(attack_speed));
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, -30, 30, 0, (int)attack_range_set, base_height, 10);
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, -20, 20, 0, (int)attack_range_set * 2, base_height, 10);

	this->setSkillAttackGroup(new SkillAttackGroup(end_attack_frame));
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, -30, 30, 0, (int)attack_range_set, base_height, 10);
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, -20, 20, 0, (int)attack_range_set * 2, base_height, 10);
	this->_skill_attack_list[this->_skill_attack_max - 1]->setSkillAttack(2, -10, 10, 0, attack_range, base_height, 10);
}