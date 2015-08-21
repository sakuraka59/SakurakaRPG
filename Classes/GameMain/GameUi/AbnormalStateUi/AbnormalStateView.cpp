#include "AbnormalStateView.h"
#include "../../chara/abnormal_state/StateBase.h"

AbnormalStateView::AbnormalStateView(StateBase* state_obj) {
	this->_state_obj = state_obj;


	string name_string_data = this->_state_obj->getStateName();

	this->_state_name_label = LabelTTF::create(name_string_data, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, this->_FONT_SIZE), cocos2d::TextHAlignment::LEFT);

	this->_state_name_label->setColor(cocos2d::Color3B(255, 255, 255));
	auto anchor_point_type = new cocos2d::Vec2(0, 1);
	this->_state_name_label->setAnchorPoint(*anchor_point_type);


	this->_state_name_label->setPosition(0, 0);


	this->addChild(this->_state_name_label);

	// デバッグ用 ---------------------------------------------------
	
	int repair_frame = this->_state_obj->getRepairFrame();
	int now_frame = this->_state_obj->getNowFrame();

	string debug_string_data = to_string(now_frame) + "/" + to_string(repair_frame);

	this->_debug_time_label = LabelTTF::create(debug_string_data, "fonts/APJapanesefontT.ttf", this->_FONT_SIZE, cocos2d::Size(200, this->_FONT_SIZE), cocos2d::TextHAlignment::LEFT);

	this->_debug_time_label->setColor(cocos2d::Color3B(255, 255, 255));
	auto debug_anchor_point_type = new cocos2d::Vec2(0, 1);
	this->_debug_time_label->setAnchorPoint(*debug_anchor_point_type);


	this->_debug_time_label->setPosition(200, 0);
	this->addChild(this->_debug_time_label);
}

void AbnormalStateView::update() {
	int repair_frame = this->_state_obj->getRepairFrame();
	int now_frame = this->_state_obj->getNowFrame();

	string debug_string_data = to_string(now_frame) + "/" + to_string(repair_frame);

	this->_debug_time_label->setString(debug_string_data);
}