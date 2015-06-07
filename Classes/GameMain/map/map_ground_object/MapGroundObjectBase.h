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

// 自動型の押し続けが反応しないようにチェック
private: unordered_map<CharaBase*, bool> _active_chara_list;
private: unordered_map<CharaBase*, bool> _before_chara_list;

// 当たり判定を行うかどうか
protected: bool _hit_flag = false;

// アクション系の動作を行えるかどうか
protected: bool _action_flag = false;

// オブジェクトの状態
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


// 踏んだ時に自動発動
public: virtual void autoActive(CharaBase* chara_obj);
protected: void autoPushActive(CharaBase* chara_obj);		// 踏んだ瞬間
protected: void autoPressActive(CharaBase* chara_obj);		// 踏んでいる間
protected: void autoOnlyActive(CharaBase* chara_obj);		// 1回目のみ
protected: virtual void autoObjBehavior(CharaBase* chara_obj);

// 調べた時に発動
public: virtual void actionActive(CharaBase* chara_obj);
protected: void actionPushActive(CharaBase* chara_obj);	// 調べた瞬間
protected: void actionOnlyActive(CharaBase* chara_obj);	// 1回目のみ
protected: virtual void actionObjBehavior(CharaBase* chara_obj);
};