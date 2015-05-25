#include "DefaultStateUI.h"
#include "DefaultStateGauge.h"
#include "../chara/mainStateType.h"

#include "../GAME_SETTING.h"

DefaultStateUI::DefaultStateUI(CharaPlayer* player_obj)
{

	// 描画範囲のテスト表示
	/*
	var texture_info = Director.Instance.GL.WhiteTextureInfo;

	var sprite = new SpriteUV(){ TextureInfo = texture_info };

	//			sprite.Position = new Vector2(150,0);

	sprite.Scale = new Vector2(GameSetting._GAME_WIDTH - 150 - 160, 100);

	sprite.Color = new Vector4(0.0f, 0.0f, 1.0f, 0.5f);
	sprite.BlendMode = BlendMode.Normal;
	this.AddChild(sprite);
	this.Position = new Vector2(150, 0);
	*/
	int ui_width = GAME_WIDTH;
	int ui_height = 100;
	cocos2d::Rect rect = cocos2d::Rect(0, 0, ui_width, 100);
	cocos2d::Sprite* sprite_data = cocos2d::Sprite::create();
	
	sprite_data->setTextureRect(rect);
	sprite_data->setColor(cocos2d::Color3B(0, 0, 255));
	sprite_data->setOpacity(128);

	auto anchor_point = new cocos2d::Vec2(0, 0);
	sprite_data->setAnchorPoint(*anchor_point);
	sprite_data->setPosition(1, 0);
	this->addChild(sprite_data);

	// 各種ゲージ表示
	//*
	int gauge_height_correction = 10;
	this->_state_hp_obj = new DefaultStateGauge(player_obj, mainStateType::hp , mainStateType::excitation);
	this->_state_hp_obj->setPosition(0, 0);
	
	this->addChild(this->_state_hp_obj);
	/*
	this->_state_sp_obj = new DefaultStateGauge(player_obj, mainStateType::sp, mainStateType::honey);
	this->_state_sp_obj->setPosition(GAME_WIDTH / 2, gauge_height_correction);
	this->addChild(this->_state_sp_obj);
	*/

//	this._state_num_obj = new DefaultStateNum(player_obj);
//	this.AddChild(this._state_num_obj);

	this->setPosition(0, 500);
}
void DefaultStateUI::Update() {
	this->_state_hp_obj->Update();
//	this->_state_sp_obj->Update();
//	this->_state_num_obj->Update();
}