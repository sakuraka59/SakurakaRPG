#include "DefaultStateGauge.h"
#include "../chara/CharaPlayer.h"
#include "../GAME_SETTING.h"

DefaultStateGauge::DefaultStateGauge(CharaPlayer* player_obj, mainStateType main_type, mainStateType sexual_type, cocos2d::Color3B gauge_color) {
	this->_gauge_frame_width = this->_gauge_width + (this->_back_margin * 2);
	this->_player_obj = player_obj;

	this->_main_type = main_type;
	this->_sexual_type = sexual_type;

	// HPƒQ[ƒW‚Ì‰¼•\Ž¦ ----------------------------------

	// background frame
	int rect_width = this->_gauge_frame_width;
	cocos2d::Rect frame_rect = cocos2d::Rect(0, 0, rect_width, this->_gauge_height);
	cocos2d::Sprite* frame_sprite = cocos2d::Sprite::create();
	
	frame_sprite->setTextureRect(frame_rect);
	frame_sprite->setColor(cocos2d::Color3B(255, 255, 255));
	frame_sprite->setOpacity(255);

	auto anchor_point = new cocos2d::Vec2(0, 0);
	frame_sprite->setAnchorPoint(*anchor_point);
	frame_sprite->setPosition(0, 0);
	this->addChild(frame_sprite);

	//--------------------------------------------------------

	cocos2d::Rect bg_rect = cocos2d::Rect(0, 0, this->_gauge_width, this->_gauge_height);
	cocos2d::Sprite* bg_sprite = cocos2d::Sprite::create();

	bg_sprite->setTextureRect(bg_rect);
	bg_sprite->setColor(cocos2d::Color3B(0, 0, 0));
	bg_sprite->setOpacity(255);

	bg_sprite->setAnchorPoint(*anchor_point);
	bg_sprite->setPosition(this->_back_margin, 0);
	
	this->addChild(bg_sprite);


	cocos2d::Rect main_state_rect = cocos2d::Rect(0, 0, this->_gauge_width, this->_gauge_height - (this->_back_margin * 2));
	this->_main_state_sprite = cocos2d::Sprite::create();

	this->_main_state_sprite->setTextureRect(main_state_rect);
//	this->_main_state_sprite->setColor(cocos2d::Color3B(128, 255, 128));
	this->_main_state_sprite->setColor(gauge_color);
	this->_main_state_sprite->setOpacity(255);

	this->_main_state_sprite->setAnchorPoint(*anchor_point);
	this->_main_state_sprite->setPosition(this->_back_margin, this->_back_margin);

	this->addChild(this->_main_state_sprite);
	
}
void DefaultStateGauge::Update() {
	this->updateMainGauge();
	this->updateExcitationGauge();
}
void DefaultStateGauge::updateMainGauge() {
	double now_hp = this->_player_obj->getNowState(this->_main_type);
	double max_hp = this->_player_obj->getMaxState(this->_main_type);
	float hp_per = (float)(now_hp / max_hp);


	this->_main_state_sprite->setScaleX(hp_per);
}
void DefaultStateGauge::updateExcitationGauge() {

	double now_excitation = this->_player_obj->getNowState(this->_sexual_type);
	double max_excitation = this->_player_obj->getMaxState(this->_sexual_type);
	double excitation_per = now_excitation / max_excitation;

//	this->_sexual_sprite_top.Scale = new Vector2((int)(this->_gauge_width * excitation_per), this->_sexual_width);
//	this->_sexual_sprite_bottom.Scale = new Vector2((int)(this->_gauge_width * excitation_per), this->_sexual_width);

}
int DefaultStateGauge::getGaugeHeight() {
	return this->_gauge_height;
}
int DefaultStateGauge::getGaugeWidth() {

	return this->_gauge_frame_width;
}