#pragma once
#include "../../../RenderObject.h"
#include "../../chara/mainStateType.h"
class CharaPlayer;
class DefaultStateGauge : public RenderObject {
private: CharaPlayer* _player_obj;
private: const int _GAUGE_HEIGHT = 14;
private: const int _GAUGE_WIDTH = 600;
private: const int _BACK_MARGIN = 4;
private: int _gauge_frame_width;
private: const int _SEXUAL_HEIGHT = 2;
private: const int _SEXUAL_MARGIN = 1;

private: mainStateType _main_type;
private: mainStateType _sexual_type;

private: cocos2d::Sprite* _main_state_sprite;

private: cocos2d::Sprite* _sexual_state_sprite_top;
private: cocos2d::Sprite* _sexual_state_sprite_bottom;
private: RenderObject* _sexual_state_gauge;
		 
/*
private SpriteUV _main_sprite;
private SpriteUV _sexual_sprite_top;
private SpriteUV _sexual_sprite_bottom;
*/

public: DefaultStateGauge(CharaPlayer* player_obj, mainStateType main_type, mainStateType sexual_type, cocos2d::Color3B gauge_color);
public: void Update();
private: void updateMainGauge();
private: void updateExcitationGauge();

public: int getGaugeHeight();
public: int getGaugeWidth();
};