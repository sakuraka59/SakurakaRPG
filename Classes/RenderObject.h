#pragma once
#pragma execution_character_set("utf-8")
#include "cocos2d.h"



class RenderObject : public cocos2d::Node {

protected: double _draw_x = 0;
protected: double _draw_y = 0;
protected: double _draw_z = 0; // ジャンプや浮遊等による補正向け

public: double getDrawX();
public: double getDrawY();
public: double getDrawZ();
public: virtual cocos2d::Vec2* getDrawPosition();
public: virtual float getDrawPositionX();
public: virtual float getDrawPositionY();
};