#include "CCGauge.h"
#include "../../chara/CharaPlayer.h"
#include "../../chara/mainStateType.h"

CCGauge::CCGauge(CharaPlayer* player_obj) {

	this->_player_obj = player_obj;


	// メインステータス 
	cocos2d::Rect main_state_rect = cocos2d::Rect(0, 0, this->_GAUGE_WIDTH, this->_GAUGE_HEIGHT);
	this->_cc_state_sprite = cocos2d::Sprite::create();

	this->_cc_state_sprite->setTextureRect(main_state_rect);
	//	this->_main_state_sprite->setColor(cocos2d::Color3B(128, 255, 128));
	this->_cc_state_sprite->setColor(this->_GAUGE_COLOR);
	this->_cc_state_sprite->setOpacity(255);

	Vec2* anchor_point = new Vec2(0, 0);
	this->_cc_state_sprite->setAnchorPoint(*anchor_point);
	this->_cc_state_sprite->setPosition(this->_BACK_MARGIN, 0);

	this->addChild(this->_cc_state_sprite);


}
void CCGauge::Update() {
	this->updateGauge();
}
void CCGauge::updateGauge() {
	double now_cc = this->_player_obj->getNowState(mainStateType::cc);
	double max_cc = this->_player_obj->getMaxState(mainStateType::cc);
	float cc_per = (float)(now_cc / max_cc);
	if (cc_per > 1.0f) {
		cc_per = 1.0f;
	}
	//	hp_per = 1.0f;
	this->_cc_state_sprite->setScaleX(cc_per);
}
int CCGauge::getGaugeHeight() {
	return this->_GAUGE_HEIGHT;
}
int CCGauge::getGaugeWidth() {
	int ret_width = this->_GAUGE_WIDTH + (this->_BACK_MARGIN * 2);
	return ret_width;
}