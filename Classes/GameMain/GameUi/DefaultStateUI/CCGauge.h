#pragma once

#include "../../../RenderObject.h"

using namespace cocos2d;
class CharaPlayer;

class CCGauge : public RenderObject {
private: CharaPlayer* _player_obj;
private: const int _GAUGE_HEIGHT = 3;
private: const int _GAUGE_WIDTH = 600;
private: const int _BACK_MARGIN = 4;

private: cocos2d::Sprite* _cc_state_sprite;
//private: const Color3B _GAUGE_COLOR = Color3B(0, 128, 255);
private: const Color3B _GAUGE_COLOR = Color3B(255, 0, 0);

public: CCGauge(CharaPlayer* player_obj);
public: void Update();
private: void updateGauge();

public: int getGaugeHeight();
public: int getGaugeWidth();
};