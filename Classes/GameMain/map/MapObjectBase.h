#pragma once
#include "../../RenderObject.h"
#include "cocos2d.h"
#include <unordered_map>

enum class haveItemType;
enum class useItemId;

class ItemBase;
class UseItem;
class EquipItem;

class GameCamera;
class HitSquare;
class CharaBase;

class HaveEquipItemList;
class HaveUseItemList;

using namespace std;

class MapObjectBase : public RenderObject {

public: cocos2d::ParticleSystemQuad* test_particle;

	// object size
protected: int _OBJECT_WIDTH = 96;
protected: int _OBJECT_HEIGHT = 192;

private: bool _DRAW_FLAG = false;

//		private int _GAME_WIDTH = 960;
//		private int _GAME_HEIGHT = 544;
private: int _draw_correction_x = 0;
private: int _draw_correction_y = 30;
private: GameCamera* _camera_obj;

// hit check type 1:cercle 2:square 3:ground size square(test only)
private: int _hit_check_type = 3;
//protected: HitSquare* _hit_square_obj;

protected: HitSquare* _hit_square_obj;

private: double _anime_num = 0;
private: double _anime_move_speed = 0.3;
private: int _sanime_statue = 0;

// オブジェクト残り動作回数
protected: int _action_num = -1;
// アクション系の動作を行えるかどうか
protected: bool _action_flag = true;

// アイテム収納機能があるかどうか _action_flag = true 限定
protected: bool _item_box_flag;

private: unordered_map<haveItemType, int> _item_type_count;

//protected: unordered_map<haveItemType, unordered_map<int, EquipItem*>> _equip_item_list;
//protected: unordered_map<haveItemType, unordered_map<string, UseItem*>> _use_item_list;
protected: HaveEquipItemList* _equip_item_list;
protected: HaveUseItemList* _use_item_list;

public: MapObjectBase(int map_block_x, int map_block_y, GameCamera* camera_obj);
public: void Update();
public: int getHitCheckType();
public: HitSquare* getHitSquare();
public: void resetDrawObject();
public: void removeDrawObject();

// 調べた時に発動
public: virtual void actionActive(CharaBase* chara_obj);
protected: void actionPushActive(CharaBase* chara_obj);	// 調べた瞬間
protected: void actionCountActive(CharaBase* chara_obj);	// 1回目のみ
protected: virtual void actionObjBehavior(CharaBase* chara_obj);
public: bool getActionFlag();

// アイテムBOX系 ------------------------------------------
// 初期化系
protected: void setRandItemList();
protected: void setItemList();
private: void setItemObj(ItemBase* item_obj);
// 調べてUI開く
protected: void openItemUi();

// アイテムを取得する
public: ItemBase* getItemList(haveItemType have_item_type, int list_index);
// アイテムを入れる
public: void pushItemList(ItemBase* item_obj);
};