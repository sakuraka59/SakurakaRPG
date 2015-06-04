#pragma once
#include "../../../RenderObject.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class HitSquare;

class MapGroundObjectBase : public RenderObject {
protected: int _OBJECT_CORRECT_WIDTH = 64;
protected: int _OBJECT_CORRECT_HEIGHT = 64;

private: bool _DRAW_FLAG = false;

// �����蔻����s�����ǂ���
protected: bool _hit_flag = false;

// �A�N�V�����n�̓�����s���邩�ǂ���
protected: bool _action_flag = false;

// �I�u�W�F�N�g�̏��
protected: int _object_state = 0;

protected: HitSquare* _hit_square_obj;

protected: string _sprite_img_pass = "";
protected: Sprite* _sprite_data;

public: MapGroundObjectBase(int map_block_x, int map_block_y);
public: void Update();
public: HitSquare* getHitSquare();

public: bool getHitFlag();
public: bool getActionFlag();

};