#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"


class PartBase : public RenderObject {

private: cocos2d::Sprite* _part_sprite;
public: PartBase(std::string file_name, float origin_x = 0.0f, float origin_y = 0.0f);
};