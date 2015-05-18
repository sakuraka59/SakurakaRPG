#pragma once

#include "cocos2d.h"
#include <unordered_map>		// ハッシュテーブル
#include "../charaGroupList.h"


class PartSetBase;
class EquipSprite;
class StateList;
class CharaBase;
class EquipItem;
class ItemBase;

class SeedBase : public cocos2d::Node {
	
protected: std::string _file_name;
protected: int _file_x = 0;
protected: int _file_y = 0;


	// 円形の当たり判定の円半径
protected: double _width = 0;
	// hit chect height
protected: double _height = 0;

protected: float _scale_per = 1.0f;

	// 描画用補正
protected: int _draw_correct_x = 0;
protected: int _draw_correct_y = 0;

protected: double _run_speed = 0.1;
protected: double _walk_speed = 0.05;

	// state correction
protected: int _base_hp = 10;
protected: int _base_sp = 10;
protected: int _base_cc = 4;
		   
// 自身が所属しているグループ
protected: std::list<charaGroupList> _my_group_list;
		   
// ターゲットにしないグループ
protected: std::list<charaGroupList> _fellow_group_list;
// ターゲットにするグループ（ターゲットにしないグループ所属の場合、そちらを優先）
protected: std::list<charaGroupList> _target_group_list;
		   
// 視界範囲（敵サーチにつかう
protected: double _vision_range = 20.0;
protected: double _vision_angle = 45;// 向いている方向から左右数値分の視界 （180度方向 ± 45度とか
protected: double _unvision_range = 40.0;

// 画像描画用
public: std::unordered_map<std::string, PartSetBase*> _parts_list;

//プレイヤー用 PlayerViewに表示用
//public: std::unordered_map<std::string, EquipSprite> _view_parts_list;

protected: StateList* _seed_state_list;



public: SeedBase();
public: virtual void Update();

// 画像
protected: void setSpriteData(std::string file_name, int x, int y);

public: double getHeight();
public: double getWidthHalf();
public: int getCorrectX();
public: int getCorrectY();
public: float getScalePer();
public: double getRunSpeed();
public: double getWalkSpeed();
public: int getBaseHp();
public: int getBaseSp();
public: int getBaseCc();
public: StateList* getStateList(CharaBase* chara_obj);
protected: virtual void setStateList(CharaBase* chara_obj);

// vision data ----------------------------------------------
public: double getVisionRange();
public: double getVisionAngle();
public: double getUnvisionRange();
// search list ----------------------------------------------
public: std::list<charaGroupList> getMyGroupList();
public: std::list<charaGroupList> getFellowGroupList();
public: std::list<charaGroupList> getTargetGroupList();
// */
};
