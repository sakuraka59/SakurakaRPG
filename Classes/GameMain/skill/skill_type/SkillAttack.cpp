#include "SkillAttack.h"
#include <math.h>
#include "../../chara/CharaBase.h"
#include "../SkillAttackGroup.h"
#include "../SkillAttackData.h"


SkillAttack::SkillAttack(CharaBase* use_chara_obj, std::list<CharaBase*> *all_chara_list) : SkillBase(use_chara_obj, all_chara_list)
{
}
void SkillAttack::skillExtendInit() {
	this->_use_chara_obj->setAttackFrame(this->_set_attack_frame);
	this->_use_chara_obj->setSkillFrame(this->_set_skill_frame);

}
bool SkillAttack::updateSkillEffect() {

	//Debug.WriteLine("[SkillAttack]updateSkillEffect 0");
	if (this->_skill_attack_count >= this->_skill_attack_max) {
		//	Debug.WriteLine("[SkillAttack]end check:1");

		return true;
	}

	if (this->_attack_frame >= this->_skill_attack_list[this->_skill_attack_count]->getFrameNum()) {
		this->_skill_attack_count++;
		this->_attack_frame = 0;
	}
	if (this->_skill_attack_count >= this->_skill_attack_max) {
		//	Debug.WriteLine("[SkillAttack]end check:2");

		return true;
	}

	this->attackCheck();
	this->attackUpdateEffect();
	this->_attack_frame++;
	return false;
}

// スキル更新中に処理を行う場合に利用する
void SkillAttack::attackUpdateEffect() {

}
void SkillAttack::attackCheck() {
	SkillAttackGroup* check_attack_group = this->_skill_attack_list[this->_skill_attack_count];
	
	// attack data list
	for (int i = 0; i < check_attack_group->getSkillSize(); i++) {
		SkillAttackData* skill_attack_data = check_attack_group->getSkillAttack(i);
		if (skill_attack_data->getSkillType() == 3) {

			// @TODO 必要かどうか不明
			//this->_hitcheck_chara_list = new std::list<CharaBase*>();// = new ArrayList<charaBase>();

			if (this->_reset_count_flag == true) {
				this->_attack_reset_count++;
				this->_reset_count_flag = false;

			}
			//return;
			continue;
		}
		if (this->_reset_count_flag != true) {
			this->_reset_count_flag = true;
		}

//		for (std::list<CharaBase*>::iterator chara_iterator = this->_all_chara_list.begin(); chara_iterator != this->_all_chara_list.end(); chara_iterator++) {
//		CharaBase* check_chara_obj = *chara_iterator;
		auto hoge = this->_all_chara_list;
		for (CharaBase* check_chara_obj : *this->_all_chara_list) {
			

			if (check_chara_obj == this->_use_chara_obj) {
				continue;
			}

			// @TODO あっち系のスキルを除外したほうがいいかもしれない？
			if (check_chara_obj->getDownFlag() == true) {
				continue;
			}

			// before hit check
			bool hit_flag = false;
			// すでにヒット済みのキャラクターを探す。空なら誰もいないから処理しないよ
			if (this->_hitcheck_chara_list.empty() != true) {
//				foreach(CharaBase hit_chara_obj in this->_hitcheck_chara_list) {
//				for (std::list<CharaBase*>::iterator chara_iterator = this->_all_chara_list.begin(); chara_iterator != this->_all_chara_list.end(); chara_iterator++) {
//					CharaBase* hit_chara_obj = *chara_iterator;
				for (CharaBase* hit_chara_obj : *this->_all_chara_list) {

					if (hit_chara_obj == check_chara_obj) {
						hit_flag = true;
						break;
					}
				}
			}
			if (hit_flag == true) {
				continue;
			}


			switch (skill_attack_data->getSkillType()) {
			case 2:

				double range = this->getTargetRange(
					this->_use_chara_obj->getDrawX(),
					this->_use_chara_obj->getDrawY(),
					check_chara_obj->getDrawX(),
					check_chara_obj->getDrawY()
					);
				double target_angle = this->getTargetAngle(
					this->_use_chara_obj->getDrawX(),
					this->_use_chara_obj->getDrawY(),
					check_chara_obj->getDrawX(),
					check_chara_obj->getDrawY()
					);

				// skill_use_chara to other chara check angle
				double chara_angle = this->_use_chara_obj->getMoveAnagleDirection();
				double target_angle_min = chara_angle + skill_attack_data->_check_a_1;
				double target_angle_max = chara_angle + skill_attack_data->_check_a_2;
				bool angle_check_flag = false;
				double max_angle = 360;

				//	Debug.WriteLine("["+this->GetType()+"]angle check:"+target_angle_max+">="+target_angle+">="+target_angle_min);
				if (target_angle >= target_angle_min &&
					target_angle <= target_angle_max) {

					angle_check_flag = true;

				}
				if (angle_check_flag == false && target_angle_min < 0) {

					if (target_angle >= target_angle_min + max_angle) {

						angle_check_flag = true;
					}
				}
				if (angle_check_flag == false && target_angle_max >= max_angle) {

					if (target_angle <= target_angle_max - max_angle) {

						angle_check_flag = true;
					}
				}
				//angle_check_flag = true;
				// angle check ok And range check
				if (
					(float)range >= skill_attack_data->_check_b_1 &&
					(float)range <= skill_attack_data->_check_b_2 &&
					angle_check_flag == true &&
					this->checkHeightHit(skill_attack_data, check_chara_obj) == true) {

					// hit to go damage
					this->_hitcheck_chara_list.push_back(check_chara_obj);
					this->attackHitEffect(check_chara_obj);
					this->_use_chara_obj->setTargetChara(check_chara_obj);
				}

				break;

			}
			
		}


		/*
		// all chara check
		foreach(CharaBase check_chara_obj in this->_all_chara_list) {

			if (check_chara_obj == this->_use_chara_obj) {
				continue;
			}

			if (check_chara_obj.getDownFlag() == true) {
				continue;
			}

			// before hit check
			bool hit_flag = false;
			if (this->_hitcheck_chara_list != null) {
				foreach(CharaBase hit_chara_obj in this->_hitcheck_chara_list) {
					if (hit_chara_obj == check_chara_obj) {
						hit_flag = true;
						break;
					}
				}
			}
			if (hit_flag == true) {
				continue;
			}


			switch (skill_attack_data.getSkillType()) {
			case 2:

				double range = this->getTargetRange(
					this->_use_chara_obj.getDrawX(),
					this->_use_chara_obj.getDrawY(),
					check_chara_obj.getDrawX(),
					check_chara_obj.getDrawY()
					);
				double target_angle = this->getTargetAngle(
					this->_use_chara_obj.getDrawX(),
					this->_use_chara_obj.getDrawY(),
					check_chara_obj.getDrawX(),
					check_chara_obj.getDrawY()
					);

				// skill_use_chara to other chara check angle
				double chara_angle = this->_use_chara_obj.getMoveAnagleDirection();
				double target_angle_min = chara_angle + skill_attack_data._check_a_1;
				double target_angle_max = chara_angle + skill_attack_data._check_a_2;
				bool angle_check_flag = false;
				double max_angle = 360;

				//	Debug.WriteLine("["+this->GetType()+"]angle check:"+target_angle_max+">="+target_angle+">="+target_angle_min);
				if (target_angle >= target_angle_min &&
					target_angle <= target_angle_max) {

					angle_check_flag = true;

				}
				if (angle_check_flag == false && target_angle_min < 0) {

					if (target_angle >= target_angle_min + max_angle) {

						angle_check_flag = true;
					}
				}
				if (angle_check_flag == false && target_angle_max >= max_angle) {

					if (target_angle <= target_angle_max - max_angle) {

						angle_check_flag = true;
					}
				}
				//	Debug.WriteLine("["+this->GetType()+"]range check:"+skill_attack_data._check_b_2+">="+range+">="+skill_attack_data._check_b_1);
				//angle_check_flag = true;
				// angle check ok And range check
				if (
					(float)range >= skill_attack_data._check_b_1 &&
					(float)range <= skill_attack_data._check_b_2 &&
					angle_check_flag == true &&
					this->checkHeightHit(skill_attack_data, check_chara_obj) == true) {

					// hit to go damage
					this->_hitcheck_chara_list.Add(check_chara_obj);
					this->attackHitEffect(check_chara_obj);
					this->_use_chara_obj.setTargetChara(check_chara_obj);
				}
				
				break;

			}
			
		}
		*/
		//check_attack_group.getSkillAttack(i);
	}
}
double SkillAttack::getTargetRange(double x1, double y1, double x2, double y2){

	double dx = pow(x1 - x2, 2);
	double dy = pow(y1 - y2, 2);
	double distance = sqrt(dx + dy);

	return distance;
}
double SkillAttack::getTargetAngle(double x1, double y1, double x2, double y2) {

	double mx = x1 - x2;
	double my = y1 - y2;

	double degree;

	if (mx == 0 && my == 0) {
		degree = 0;
	}
	else {
		degree = atan2(my, mx) * (180 / M_PI);
	}
	return degree + 180;
}
bool SkillAttack::checkHeightHit(SkillAttackData* skill_attack_data, CharaBase* check_chara_obj) {

	//return true;
	float hit_height_base = (float)this->_use_chara_obj->getDrawZ() + skill_attack_data->_attack_height_base;
	float hit_height_top = skill_attack_data->_attack_height + hit_height_base;
	float chara_height_top = (float)(check_chara_obj->getDrawZ() + check_chara_obj->getHitHeight());

	//	Debug.WriteLine("["+this->GetType()+"]height top  check:"+hit_height_top+">="+check_chara_obj.getDrawZ());
	//	Debug.WriteLine("["+this->GetType()+"]height base check:"+hit_height_base+"<="+chara_height_top);
	if (hit_height_top >= check_chara_obj->getDrawZ() &&
		hit_height_base <= chara_height_top) {

		return true;
	}
	return false;
}
double SkillAttack::getNpcUseRange() {
	return this->_npc_use_range;
}