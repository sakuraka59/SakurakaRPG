#include "DefaultStateGauge.h"
#include "../../chara/CharaPlayer.h"
#include "../../GAME_SETTING.h"

DefaultStateGauge::DefaultStateGauge(CharaPlayer* player_obj, mainStateType main_type, mainStateType sexual_type, cocos2d::Color3B gauge_color) {
	this->_gauge_frame_width = this->_GAUGE_WIDTH + (this->_BACK_MARGIN * 2);
	this->_player_obj = player_obj;

	this->_main_type = main_type;
	this->_sexual_type = sexual_type;

	// HPゲージの仮表示 ----------------------------------

	// ゲージ端のフレーム
	int rect_width = this->_gauge_frame_width;
	cocos2d::Rect frame_rect = cocos2d::Rect(0, 0, rect_width, this->_GAUGE_HEIGHT);
	cocos2d::Sprite* frame_sprite = cocos2d::Sprite::create();
	
	frame_sprite->setTextureRect(frame_rect);
	frame_sprite->setColor(cocos2d::Color3B(255, 255, 255));
	frame_sprite->setOpacity(255);

	auto anchor_point = new cocos2d::Vec2(0, 0);
	frame_sprite->setAnchorPoint(*anchor_point);
	frame_sprite->setPosition(0, 0);
	this->addChild(frame_sprite);

	//--------------------------------------------------------

	// ゲージ背景
	cocos2d::Rect bg_rect = cocos2d::Rect(0, 0, this->_GAUGE_WIDTH, this->_GAUGE_HEIGHT);
	cocos2d::Sprite* bg_sprite = cocos2d::Sprite::create();

	bg_sprite->setTextureRect(bg_rect);
	bg_sprite->setColor(cocos2d::Color3B(0, 0, 0));
	bg_sprite->setOpacity(255);

	bg_sprite->setAnchorPoint(*anchor_point);
	bg_sprite->setPosition(this->_BACK_MARGIN, 0);
	
	this->addChild(bg_sprite);


	// メインステータス HP or SP
	cocos2d::Rect main_state_rect = cocos2d::Rect(0, 0, this->_GAUGE_WIDTH, this->_GAUGE_HEIGHT - (this->_BACK_MARGIN * 2));
	this->_main_state_sprite = cocos2d::Sprite::create();

	this->_main_state_sprite->setTextureRect(main_state_rect);
//	this->_main_state_sprite->setColor(cocos2d::Color3B(128, 255, 128));
	this->_main_state_sprite->setColor(gauge_color);
	this->_main_state_sprite->setOpacity(255);

	this->_main_state_sprite->setAnchorPoint(*anchor_point);
	this->_main_state_sprite->setPosition(this->_BACK_MARGIN, this->_BACK_MARGIN);

	this->addChild(this->_main_state_sprite);

	// サブステータス honey or excitation
	cocos2d::Color3B sexual_garge_color = cocos2d::Color3B(255, 128, 128);
	cocos2d::Rect sexual_state_rect = cocos2d::Rect(0, 0, this->_GAUGE_WIDTH, this->_SEXUAL_HEIGHT);
	this->_sexual_state_sprite_top = cocos2d::Sprite::create();
	
	this->_sexual_state_sprite_top->setTextureRect(sexual_state_rect);
	this->_sexual_state_sprite_top->setColor(sexual_garge_color);
	this->_sexual_state_sprite_top->setOpacity(255);

	this->_sexual_state_sprite_top->setAnchorPoint(*anchor_point);
	this->_sexual_state_sprite_top->setPosition(0, 0 + this->_SEXUAL_MARGIN);


	this->_sexual_state_sprite_bottom = cocos2d::Sprite::create();

	this->_sexual_state_sprite_bottom->setTextureRect(sexual_state_rect);
	this->_sexual_state_sprite_bottom->setColor(sexual_garge_color);
	this->_sexual_state_sprite_bottom->setOpacity(255);

	this->_sexual_state_sprite_bottom->setAnchorPoint(*anchor_point);
	this->_sexual_state_sprite_bottom->setPosition(0, this->_GAUGE_HEIGHT - this->_SEXUAL_HEIGHT - this->_SEXUAL_MARGIN);

	this->_sexual_state_gauge = new RenderObject();
	this->_sexual_state_gauge->setPosition(this->_BACK_MARGIN, 0);
	this->_sexual_state_gauge->addChild(this->_sexual_state_sprite_top);
	this->_sexual_state_gauge->addChild(this->_sexual_state_sprite_bottom);

	this->addChild(this->_sexual_state_gauge);
}
void DefaultStateGauge::Update() {
	this->updateMainGauge();
	this->updateExcitationGauge();
}
void DefaultStateGauge::updateMainGauge() {
	double now_hp = this->_player_obj->getNowState(this->_main_type);
	double max_hp = this->_player_obj->getMaxState(this->_main_type);
	float hp_per = (float)(now_hp / max_hp);

//	hp_per = 1.0f;
	this->_main_state_sprite->setScaleX(hp_per);
}
void DefaultStateGauge::updateExcitationGauge() {

	double now_excitation = this->_player_obj->getNowState(this->_sexual_type);
	double max_excitation = this->_player_obj->getMaxState(this->_sexual_type);
	float excitation_per = (float)(now_excitation / max_excitation);

//	excitation_per = 0.10f;
	this->_sexual_state_gauge->setScaleX(excitation_per);
}
int DefaultStateGauge::getGaugeHeight() {
	return this->_GAUGE_HEIGHT;
}
int DefaultStateGauge::getGaugeWidth() {
	return this->_gauge_frame_width;
}