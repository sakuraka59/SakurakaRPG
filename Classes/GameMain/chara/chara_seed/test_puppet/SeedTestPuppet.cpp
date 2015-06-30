#include "SeedTestPuppet.h"
#include "../human/human_part/HumanTest.h"
#include "../../abnormal_state/abnormalStateType.h"
#include "../../abnormal_state/StateList.h"

SeedTestPuppet::SeedTestPuppet(CharaBase* chara_obj) : SeedBase(chara_obj) {

	// state base -------------------------------------------
	this->_run_speed = 0;//0.5;
	this->_walk_speed = 0;//0.2;
	this->_base_hp = 500;
	this->_base_sp = 2000;

	this->_vision_range = 150.0;
	this->_vision_angle = 50;
	this->_unvision_range = 200.0;

	this->_width = 8;
	this->_height = 16;

	// set group --------------------------------------------
	// my group
	this->_my_group_list.push_back(charaGroupList::thief);

	// no target group
	this->_fellow_group_list.push_back(charaGroupList::thief);

	// target group
	this->_target_group_list.push_back(charaGroupList::human);

	/*
	this->_parts_list.Add("body", new TentacleBody());
	this->addChild(this->_parts_list["body"]);
	*/

	this->_parts_list["body"] = new HumanTest(this->_chara_obj);
	this->addChild(this->_parts_list["body"]);
	
	this->_draw_correct_x = (int)((float)(340 / 2) *0.20f);
	this->_draw_correct_y = 0;

	this->_scale_per = 1.0f;//0.22f;
	this->setScale(this->_scale_per);

	/*
	this->_parts_list["body"] = std::make_unique<HumanTest>();
	this->addChild(this->_parts_list["body"].get());
	*/
}
void SeedTestPuppet::setStateList(CharaBase* chara_obj) {
	//this->_seed_state_list.setSeedStateResist(abnormalStateType.oestrus, 10000);
	this->_seed_state_list->setStateGuard(abnormalStateType::oestrus);
}