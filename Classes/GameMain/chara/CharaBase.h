#pragma once

#include "../../RenderObject.h"
#include <unordered_map>		// ハッシュテーブル
#include "mainStateType.h"
#include "equipType.h"
#include "abnormal_state/StateBase.h"
#include "../item/equip_item/EquipItem.h"


class SeedBase;
class StateList;

class EquipItem;
class HaveUseItemList;
class HaveEquipItemList;

class GameCamera;
class ShadowObjectList;
//*/
// enum
// mainStateType, charaGroupList, charaSexualState, charaSexualType
// equipType,

// class
// SeedBase, StateList, 
// HaveUseItemList, HaveEquipItemList,
// SkillList, SkillAttack, SkillBase
// GameCamera, ShadowObjectList,

class CharaBase : public RenderObject
{

// 補正なしステータス
public: std::unordered_map<mainStateType, int> _base_state;
//	protected Dictionary<mainStateType, int> _base_state = new Dictionary<mainStateType, int>();

// 補正のみのステータス
public: std::unordered_map<mainStateType, int> _correction_state;
//	protected Dictionary<mainStateType, int> _correction_state = new Dictionary<mainStateType, int>();

// 現在ステータス
public: std::unordered_map<mainStateType, int> _now_state;
//	protected Dictionary<mainStateType, int> _now_state = new Dictionary<mainStateType, int>();

// 最大ステータス（HPやSPなど限定
public: std::unordered_map<mainStateType, int> _max_state;
//	protected Dictionary<mainStateType, int> _max_state = new Dictionary<mainStateType, int>();


// 現在装備しているアイテム
protected: std::unordered_map<equipType, EquipItem> _equip_list;

// 自身が所属しているグループ
//	protected List<charaGroupList> _my_group_list = new List<charaGroupList>();

	//	Correction	補正
protected: double _hit_height = 0;
protected: double _hit_width_half = 0;

protected: double _run_speed_base = 0;		// 基本移動速度
protected: double _run_speed = 0;			// 補正込み移動速度
protected: double _walk_speed = 0;			// 歩き速度（一定）

//protected: SeedBase _chara_seed;

// 移動に関する要素
protected: double _move_angle = 0.0;			// 移動方向
protected: int _move_angle_direction = 0;	// 移動方向ステータス（0, 45, 90, 135, 180, 225, 270, 315, 360）
protected: double _move_speed_per = 100.0f;	// 走る速度
protected: double _move_x = 0.0; 			// Xのみの移動距離
protected: double _move_y = 0.0; 			// Yのみの移動距離

		   // マップブロック上の座標
protected: int _map_block_x = 0;
protected: int _map_block_y = 0;

// 1フレーム前の座標（更新はUpdateDrawの最後に行う
protected: double _before_x = 0;
protected: double _before_y = 0;


protected: double _jump_speed = 0;	// 1frame to draw_z speed
private: double _fall_speed = 0.3;	// gravity

// 行動に冠する要素
protected: int _no_control_frame = 0;	// 1以上ですべての行動が不可能。 1フレームに1減少する
protected: int _attack_frame = 0;		// 移動やジャンプなどの行動が不可能になる時間。スキルによるキャンセルは可能
protected: int _skill_frame = 0;			// スキルのキャンセルが可能になるまでの時間。0になるとスキルが使用可能（通常攻撃も含め）

protected: int _spell_status = 0;		// 魔法の詠唱状態 0：通常 1：方向指定の詠唱 2：位置指定の詠唱
private: double _spell_point_x = 0;		// 魔法を放つ座標X。自身の座標からの相対座標なので注意。
private: double _spell_point_y = 0;		// 魔法を放つ座標Y。自身の座標からの相対座標なので注意。
private: double _spell_point_speed = 2.0;	// 魔法座標の移動速度

protected: int _super_armour_frame = 0;	// スーパーアーマーの時間。0より多い場合、攻撃を受けてもこちらの行動がキャンセルされなくなる。
protected: bool _down_flag = false;		// hpが0になって戦闘続行不可能な状態かどうか
protected: int _REVIVAL_TIME = 120;		// HPが0になってから復帰するまでにかかる時間
protected: int _revival_frame = 0;		// 復帰までの残り秒数。ダウン直後は _REVIVAL_TIMEの値が代入される

protected: int _push_frame = 0;			// 吹き飛ばし時間
protected: double _push_angle = 0;		// 吹き飛ばし方向
protected: double _push_speed = 0;		// 吹き飛ばし速度

protected: int _weapon_state = 0;		// 武器の構え等の状態。主に片手直剣+鞘での抜刀剣で使用する

// 状態異常ステータスリスト
//protected StateList _state_list;

// 性的に関する状態。コメントでのみ使用すること
//protected charaSexualState _sexual_state = charaSexualState.normal;
//protected charaSexualType _sexual_type = charaSexualType.no_type;

// 1回目の火照り→発情にて使うﾌﾗｸﾞ
protected: bool now_hot_to_oestrus_flag = false;

// 性的に関する要素。自動回復用
protected: int _sexual_repair_frame = 0;
protected: int _SEXUAL_SET_FRAME = 120;
protected: int _AUTO_HEAL_HONEY = 2;
protected: int _AUTO_HEAL_EXCITATION = 1;

// 描画用補正
protected: int _draw_correct_x = 0;
protected: int _draw_correct_y = 0;

//protected: GameCamera _play_camera;

// 各種オブジェクトのリスト
protected: std::list<CharaBase> _all_chara_list;
//protected SkillList _skill_list;
//protected List<MagicBase> _magic_list;
//protected ShadowObjectList _shadow_list;

// 所持アイテム
//protected HaveUseItemList _use_item_list;
//protected HaveEquipItemList _equip_item_list;


// 敵に使おうとしているスキル
// TODO NPCのAIのみで使用している。下記の使用中スキルで代替できるようにしたい
//protected SkillAttack _set_attack_skill = null;
// 現在使用中のスキル
//protected SkillBase _set_now_skill = null;

// スキル使用中によるターゲット追尾
//protected CharaBase _skill_target_obj = null;
private: int _skill_chain_num;


};
