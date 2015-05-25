#pragma once
#include "../../RenderObject.h"
#include "../chara/mainStateType.h"
class CharaPlayer;
class DefaultStateGauge : public RenderObject {
private: CharaPlayer* _player_obj;
private: int _gauge_height = 16;
private: int _gauge_width = 800;
private: int _back_margin = 4;
private: int _gauge_frame_width;
private: int _sexual_width = 2;

private: mainStateType _main_type;
private: mainStateType _sexual_type;

private: cocos2d::Rect _main_state_rect;
private: cocos2d::Sprite* _main_state_sprite;
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