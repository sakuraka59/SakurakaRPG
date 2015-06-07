#pragma once
#include "../../../RenderObject.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class HitSquare;
class CharaBase;

class MapGroundObjectBase : public RenderObject {
protected: int _OBJECT_CORRECT_WIDTH = 64;
protected: int _OBJECT_CORRECT_HEIGHT = 64;

private: bool _DRAW_FLAG = false;

// �����^�̉����������������Ȃ��悤�Ƀ`�F�b�N
private: unordered_map<CharaBase*, bool> _active_chara_list;
private: unordered_map<CharaBase*, bool> _before_chara_list;

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

public: virtual void Update();
public: virtual void UpdateInit();
public: HitSquare* getHitSquare();

public: bool getHitFlag();
public: bool getActionFlag();


// ���񂾎��Ɏ�������
public: virtual void autoActive(CharaBase* chara_obj);
protected: void autoPushActive(CharaBase* chara_obj);		// ���񂾏u��
protected: void autoPressActive(CharaBase* chara_obj);		// ����ł����
protected: void autoOnlyActive(CharaBase* chara_obj);		// 1��ڂ̂�
protected: virtual void autoObjBehavior(CharaBase* chara_obj);

// ���ׂ����ɔ���
public: virtual void actionActive(CharaBase* chara_obj);
protected: void actionPushActive(CharaBase* chara_obj);	// ���ׂ��u��
protected: void actionOnlyActive(CharaBase* chara_obj);	// 1��ڂ̂�
protected: virtual void actionObjBehavior(CharaBase* chara_obj);
};