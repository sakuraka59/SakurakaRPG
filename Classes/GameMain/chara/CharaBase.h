#pragma once

#include "../../RenderObject.h"
#include <unordered_map>		// ハッシュテーブル

#include "mainStateType.h"
#include "equipType.h"
#include "charaGroupList.h"
#include "abnormal_state/abnormalStateType.h"

#include "charaSexualType.h"
//charaSexualState

#include "charaCommentType.h"
#include "charaSexualType.h"
#include "charaSexualState.h"

#include "../item/equip_item/weapon/weaponType.h"

///#include "abnormal_state/StateBase.h"
//#include "../item/equip_item/EquipItem.h"

//*

class SeedBase;				// ok
class StateList;			// ok

class EquipItem;			// ok
class HaveUseItemList;		// ok
class HaveEquipItemList;	// ok 

class GameCamera;			// ok
class ShadowObjectList;		// 後で実装

class HitCircle;			// ok
class SkillBase;			// ok			
class SkillAttack;			//
class MagicBase;			// 
// PSMからの移植先どうする？
//	class Vector2; -> cocos2d::Vec2

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
protected: std::unordered_map<equipType, EquipItem*> _equip_list;

// 自身が所属しているグループ
protected: std::list<charaGroupList> _my_group_list;

//	Correction	補正
protected: double _hit_height = 0;
protected: double _hit_width_half = 0;

protected: double _run_speed_base = 0;		// 基本移動速度
protected: double _run_speed = 0;			// 補正込み移動速度
protected: double _walk_speed = 0;			// 歩き速度（一定）

protected: SeedBase* _chara_seed;

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
protected: StateList* _state_list;

// 性的に関する状態。コメントでのみ使用すること
protected: charaSexualState _sexual_state = charaSexualState::normal;
protected: charaSexualType _sexual_type = charaSexualType::no_type;

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

protected: GameCamera* _play_camera;

// 各種オブジェクトのリスト
protected: std::list<CharaBase*> *_all_chara_list;
//protected: SkillList* _skill_list;
protected: std::list<MagicBase*>* _magic_list;
protected: ShadowObjectList* _shadow_list;

// 所持アイテム
protected: HaveUseItemList* _use_item_list;
protected: HaveEquipItemList* _equip_item_list;

// 敵に使おうとしているスキル
// TODO NPCのAIのみで使用している。下記の使用中スキルで代替できるようにしたい
protected: SkillAttack* _set_attack_skill;

// 現在使用中のスキル
protected: SkillBase* _set_now_skill;
//protected: std::unique_ptr<SkillBase> _set_now_skill;

// スキル使用中によるターゲット追尾
protected: CharaBase* _skill_target_obj;
private: int _skill_chain_num;

// 当たり判定
//protected: std::unique_ptr<HitCircle>& _hit_circle_obj;
protected: HitCircle* _hit_circle_obj;

protected: std::string _test_label;
protected: cocos2d::LabelTTF* _label_obj;


//-------------------------------------------------------------------
public: CharaBase();
protected: void SetCharaHitData();
public: void Update();
protected: virtual void mainUpdate();
protected: void updateBlockPoint();
protected: void commonUpdate();
protected: void charaDownMoment();
public: bool getDownFlag();
protected: virtual void charaDownMomentDetail();
protected: void charaDownUpdate();
//-----------------------------------------------------------
// キャラクターが復活した際の処理
//-----------------------------------------------------------
protected: virtual void charaRevival();
public: void allActionCancel();
//-----------------------------------------------------------
// キャラクターの移動の更新処理を行う
//-----------------------------------------------------------
protected: void updateMove(double move_speed = 0);
public: void updateMagicPoint();
// jump
public: bool setJumpNormal(double jump_speed);
public: bool setJumpForcing(double jump_speed);
private: void updateJump();

public: bool checkGroundFlag();
// skill to move
public: void updateSkillMove(double add_angle, double move_speed_1frame, double jump_power);

public: void updateDraw();
public: cocos2d::Vec2* getDrawPosition() override;
public: float getDrawPositionX() override;
public: float getDrawPositionY() override;
public: void updateMoveAngle(double angle);
public: void updateMoveAngleDirection();
public: int getMoveAnagleDirection();

//	詠唱中の方向変更や位置の更新
public: void updateSpellAim(double angle);


public: SeedBase* getCharaSeed();
public: HitCircle* getHitCircle();
public: void setRunSpeedBase(double speed);
public: void setRunSpeed();
public: double getRunSpeed();
public: void setWalkSpeed(double speed);
public: double getWalkSpeed();
public: double getMoveAngle();

//-----------------------------------------------------------
// 行動に冠する要素の関数
//-----------------------------------------------------------
public: void setNoControlFrame(int frame_num);

// 攻撃後のスキル以外の行動が可能になるまでの時間をセット
public: void setAttackFrame(int frame_num);

// 次のスキルが使えるようになるまでの時間を取得
public: void setSkillFrame(int frame_num);

// 詠唱状態をセットする
public: void setSpellStatus(int spell_state);

// 詠唱状態から復帰する
public: void resetSpellStatus();

public: void setSuperAromurFrame(int frame_num);

public: int getNoControlFrame();
public: int getAttackFrame();
//------------------------------------------------------------------------------------------------
public: int getSkillFrame();
public: int getSuperAromurFrame();
protected: void setState();
private: void setStateInit(mainStateType state_type, int num);
public: int getNowState(mainStateType state_type);
public: int getBaseState(mainStateType state_type);
public: int getCorrectionState(mainStateType state_type);
public: int getMaxState(mainStateType state_type);
public: void addCorrectionState(mainStateType state_type, int num);
private: void calNowState(mainStateType state_type);
public: double getHitHeight();
public: int getNowHp();
public: void setBeforeInsertDraw();
private: void setDrawXToBeforeX();
private: void setDrawYToBeforeY();
public: void setDrawX(double set_x);
public: void setDrawY(double set_y);
public: double getBeforeX();
public: double getBeforeY();
public: int getMapBlockX();
public: int getMapBlockY();

// group data -----------------------------------------------
protected: virtual void setGroupList();
public: std::list<charaGroupList> getMyGroupList();

//-----------------------------------------------------------
// equip item
//-----------------------------------------------------------
public: void setEquipItem(equipType equip_type, EquipItem* item_obj, std::unordered_map<abnormalStateType, int> abnormal_state_list);

public: void removeEquipItem(equipType equip_type, EquipItem* item_obj, std::unordered_map<abnormalStateType, int> abnormal_state_list);

public: void reColStatus(mainStateType state_type);
public: void setEquipToAbnormalState(abnormalStateType state_type, EquipItem* item_obj);
public: void removeEquipToAbnormalState(abnormalStateType state_type, EquipItem* item_obj);

// get set data etc -----------------------------------------
public: std::list<CharaBase*>* getAllCharaList();
public: StateList* getStateList();

public: bool setSkill(SkillBase* skill_obj);
private: bool checkSetSkill(SkillBase* skill_obj);

private: void countActionFrame();
public: bool checkAttackFlag();
public: bool checkActionFlag();
public: bool checkSpellFlag();

// sp -------------------------------------------------------
private: void useSp(int use_sp);
public: bool checkSp(int check_sp);

// damage ---------------------------------------------------
public: void slipDamageHp(int damage);
public: void directDamageHp(int damage);
public: void normalDamageHp(int attack_damage);
public: void checkToSetState(abnormalStateType state_type, int state_level, int state_rate);
public: virtual void damageAction();
public: void checkRemoveSkill();
public: void removeSkill();
// sexual damage ----------------------------------
public: void normalDamageSexual(int damage, double direct_rate, bool action_flag = false, charaCommentType comment_type = charaCommentType::no_type);
public: void honeyOnlyDamage(int damage, bool action_flag = false);
public: void setExtasy();
public: void resetRevivalFrame();
// sexual etc -----------------------------------------------
public: charaSexualType getSexualType();
// heal -----------------------------------------------------
public: void healHp(int heal_num);
public: void autoHealSexual();
// test only ------------------------------------------------
protected: int _test_weapon_index = -1;
public: void setWeaponTestIndex(int index);

// send comment (use to player only -------------------------
public: virtual void sendComment(std::string comment);
public: virtual void sendTypeComment(charaCommentType comment_type, charaSexualType chara_type);
public: virtual void sendTypeCommentDirect(charaCommentType comment_type, charaSexualType chara_type);
public: virtual void sendSexualComment();

// set magic list
public: void setMagicList(MagicBase* magic_obj);

public: void setShadowList(MagicBase* magic_obj);

public: GameCamera* getGameCamera();

// equip data -----------------------------------------------
public: weaponType getMainWeaponType();
public: weaponType getSubWeaponType();

//-----------------------------------------------------------
// 剣+鞘などで使う武器状態を取得
//-----------------------------------------------------------
public: int getWeaponState();
public: void setWeaponState(int weapon_state);
public: EquipItem* getEquipItemObj(equipType equip_type);
// magic ----------------------------------------------------
public: double getSpellPointX();
public: double getSpellPointY();
// push -----------------------------------------------------
public: void setDamagePush(double push_speed, double push_angle, int push_frame);
private: void updateDamagePush();

// battle target --------------------------------------------
public: void setTargetChara(CharaBase* set_target_chara_obj);

//-----------------------------------------------------------
//	ターゲットの方向を取得する
//-----------------------------------------------------------
private: double getTargetAngleSkill();
private: void resetTargetChara();
protected: double getTargetAngle(double x1, double y1, double x2, double y2);



// マップ移動による初期位置設定
public: virtual void setCharaMapPoint(double point_x, double point_y);
};
