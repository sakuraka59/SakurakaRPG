#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"


enum class partsAngleType {
	no_type = 0,
	front		= 1,	// ����
	front_left,			// ���ʉE
	left,				// �E
	back_left,			// �w�ʉE
	back,				// �w��
	back_right,			// �w�ʍ�
	right,				// ��
	front_right,		// ���ʍ�
	enum_end,
};
class PartBase : public RenderObject {

private: cocos2d::Sprite* _part_sprite;
public: PartBase(std::string file_name, float origin_x = 0.0f, float origin_y = 0.0f);
};