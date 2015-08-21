#include "AbnormalStateUI.h"
#include "AbnormalStateUi/AbnormalStateView.h"

#include "../chara/CharaPlayer.h"
#include "../chara/abnormal_state/StateBase.h"
#include "../chara/abnormal_state/StateList.h"

#include "../GAME_SETTING.h"

AbnormalStateUI::AbnormalStateUI(){
}
void AbnormalStateUI::setInit(CharaPlayer* player_obj) {



	this->_player_obj = player_obj;
	StateList* state_list_obj = player_obj->getStateList();
	this->_state_list = state_list_obj->getStateList();

//	map<abnormalStateType, StateBase*> sortedHash(this->_state_list.begin(), this->_state_list.end());

	this->setDrawList();

	this->setPosition(0, GAME_HEIGHT);
}
void AbnormalStateUI::setDrawList() {
	int set_count = 0;

	for (auto state_obj_base : this->_state_list) {
		StateBase* state_obj = state_obj_base.second;
		/*
		string string_data = state_obj->getStateName();

		this->_state_name_label_list[state_obj] = LabelTTF::create(string_data, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, this->_FONT_SIZE), cocos2d::TextHAlignment::LEFT);

		this->_state_name_label_list[state_obj]->setColor(cocos2d::Color3B(255, 255, 255));
		auto anchor_point_type = new cocos2d::Vec2(0, 1);
		this->_state_name_label_list[state_obj]->setAnchorPoint(*anchor_point_type);

		int draw_set_y = ((this->_FONT_SIZE + this->_BOTTOM_MARGIN) * set_count) * (-1);
		this->_state_name_label_list[state_obj]->setPosition(0, draw_set_y);


		this->addChild(this->_state_name_label_list[state_obj]);
		*/
		if (this->_state_view_list[state_obj] == nullptr) {
			this->_state_view_list[state_obj] = new AbnormalStateView(state_obj);
		}

		int draw_set_y = ((this->_FONT_SIZE + this->_BOTTOM_MARGIN) * set_count) * (-1);
		this->_state_view_list[state_obj]->setPosition(0, draw_set_y);
		this->addChild(this->_state_view_list[state_obj]);

		set_count++;
	}
}
void AbnormalStateUI::Update() {
	for (auto state_view_base : this->_state_view_list) {
		state_view_base.second->update();
	}
}