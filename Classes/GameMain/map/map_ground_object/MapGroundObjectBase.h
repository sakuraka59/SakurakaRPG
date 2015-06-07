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

// 当たり判定を行うかどうか
protected: bool _hit_flag = false;

// アクション系の動作を行えるかどうか
protected: bool _action_flag = false;

// オブジェクトの状態
protected: int _object_state = 0;

protected: HitSquare* _hit_square_obj;

protected: string _sprite_img_pass = "";
protected: Sprite* _sprite_data;

private: list<CharaBase*> _active_chara_list;
private: list<CharaBase*> _before_chara_list;


public: MapGroundObjectBase(int map_block_x, int map_block_y);

public: virtual void Update();
public: virtual void UpdateInit();
public: HitSquare* getHitSquare();

public: bool getHitFlag();
public: bool getActionFlag();
public: void activeObject(CharaBase* chara_obj);

// 踏んだ時に自動発動
public: void autoPushActive(CharaBase* chara_obj);		// 踏んだ瞬間
public: void autoPressActive(CharaBase* chara_obj);		// 踏んでいる間
public: void autoOnlyActive(CharaBase* chara_obj);		// 1回目のみ

// 調べた時に発動
public: void actionPushActive(CharaBase* chara_obj);	// 調べた瞬間
public: void actionOnlyActive(CharaBase* chara_obj);	// 1回目のみ
};