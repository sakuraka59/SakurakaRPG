#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"


enum class partsAngleType {
	no_type = 0,
	front		= 1,	// ê≥ñ 
	front_left,			// ê≥ñ âE
	left,				// âE
	back_left,			// îwñ âE
	back,				// îwñ 
	back_right,			// îwñ ç∂
	right,				// ç∂
	front_right,		// ê≥ñ ç∂
	enum_end,
};
class PartBase : public RenderObject {

private: cocos2d::Sprite* _part_sprite;
public: PartBase(std::string file_name, float origin_x = 0.0f, float origin_y = 0.0f);
};