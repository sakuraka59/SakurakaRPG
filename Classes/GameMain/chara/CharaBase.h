#pragma once

#include "../../RenderObject.h"
#include <unordered_map>		// �n�b�V���e�[�u��

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
class ShadowObjectList;		// ��Ŏ���

class HitCircle;			// ok
class SkillBase;			// ok			
class SkillAttack;			//
class MagicBase;			// 
// PSM����̈ڐA��ǂ�����H
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

// �␳�Ȃ��X�e�[�^�X
public: std::unordered_map<mainStateType, int> _base_state;
//	protected Dictionary<mainStateType, int> _base_state = new Dictionary<mainStateType, int>();

// �␳�݂̂̃X�e�[�^�X
public: std::unordered_map<mainStateType, int> _correction_state;
//	protected Dictionary<mainStateType, int> _correction_state = new Dictionary<mainStateType, int>();

// ���݃X�e�[�^�X
public: std::unordered_map<mainStateType, int> _now_state;
//	protected Dictionary<mainStateType, int> _now_state = new Dictionary<mainStateType, int>();

// �ő�X�e�[�^�X�iHP��SP�Ȃǌ���
public: std::unordered_map<mainStateType, int> _max_state;
//	protected Dictionary<mainStateType, int> _max_state = new Dictionary<mainStateType, int>();

// ���ݑ������Ă���A�C�e��
protected: std::unordered_map<equipType, EquipItem*> _equip_list;

// ���g���������Ă���O���[�v
protected: std::list<charaGroupList> _my_group_list;

//	Correction	�␳
protected: double _hit_height = 0;
protected: double _hit_width_half = 0;

protected: double _run_speed_base = 0;		// ��{�ړ����x
protected: double _run_speed = 0;			// �␳���݈ړ����x
protected: double _walk_speed = 0;			// �������x�i���j

protected: SeedBase* _chara_seed;

// �ړ��Ɋւ���v�f
protected: double _move_angle = 0.0;			// �ړ�����
protected: int _move_angle_direction = 0;	// �ړ������X�e�[�^�X�i0, 45, 90, 135, 180, 225, 270, 315, 360�j
protected: double _move_speed_per = 100.0f;	// ���鑬�x
protected: double _move_x = 0.0; 			// X�݂̂̈ړ�����
protected: double _move_y = 0.0; 			// Y�݂̂̈ړ�����

// �}�b�v�u���b�N��̍��W
protected: int _map_block_x = 0;
protected: int _map_block_y = 0;

// 1�t���[���O�̍��W�i�X�V��UpdateDraw�̍Ō�ɍs��
protected: double _before_x = 0;
protected: double _before_y = 0;

protected: double _jump_speed = 0;	// 1frame to draw_z speed
private: double _fall_speed = 0.3;	// gravity

// �s���Ɋ�����v�f
protected: int _no_control_frame = 0;	// 1�ȏ�ł��ׂĂ̍s�����s�\�B 1�t���[����1��������
protected: int _attack_frame = 0;		// �ړ���W�����v�Ȃǂ̍s�����s�\�ɂȂ鎞�ԁB�X�L���ɂ��L�����Z���͉\
protected: int _skill_frame = 0;			// �X�L���̃L�����Z�����\�ɂȂ�܂ł̎��ԁB0�ɂȂ�ƃX�L�����g�p�\�i�ʏ�U�����܂߁j

protected: int _spell_status = 0;		// ���@�̉r����� 0�F�ʏ� 1�F�����w��̉r�� 2�F�ʒu�w��̉r��
private: double _spell_point_x = 0;		// ���@������WX�B���g�̍��W����̑��΍��W�Ȃ̂Œ��ӁB
private: double _spell_point_y = 0;		// ���@������WY�B���g�̍��W����̑��΍��W�Ȃ̂Œ��ӁB
private: double _spell_point_speed = 2.0;	// ���@���W�̈ړ����x

protected: int _super_armour_frame = 0;	// �X�[�p�[�A�[�}�[�̎��ԁB0��葽���ꍇ�A�U�����󂯂Ă�������̍s�����L�����Z������Ȃ��Ȃ�B
protected: bool _down_flag = false;		// hp��0�ɂȂ��Đ퓬���s�s�\�ȏ�Ԃ��ǂ���
protected: int _REVIVAL_TIME = 120;		// HP��0�ɂȂ��Ă��畜�A����܂łɂ����鎞��
protected: int _revival_frame = 0;		// ���A�܂ł̎c��b���B�_�E������� _REVIVAL_TIME�̒l����������

protected: int _push_frame = 0;			// ������΂�����
protected: double _push_angle = 0;		// ������΂�����
protected: double _push_speed = 0;		// ������΂����x

protected: int _weapon_state = 0;		// ����̍\�����̏�ԁB��ɕЎ蒼��+��ł̔������Ŏg�p����

// ��Ԉُ�X�e�[�^�X���X�g
protected: StateList* _state_list;

// ���I�Ɋւ����ԁB�R�����g�ł̂ݎg�p���邱��
protected: charaSexualState _sexual_state = charaSexualState::normal;
protected: charaSexualType _sexual_type = charaSexualType::no_type;

// 1��ڂ̉ΏƂ聨����ɂĎg���׸�
protected: bool now_hot_to_oestrus_flag = false;

// ���I�Ɋւ���v�f�B�����񕜗p
protected: int _sexual_repair_frame = 0;
protected: int _SEXUAL_SET_FRAME = 120;
protected: int _AUTO_HEAL_HONEY = 2;
protected: int _AUTO_HEAL_EXCITATION = 1;

// �`��p�␳
protected: int _draw_correct_x = 0;
protected: int _draw_correct_y = 0;

protected: GameCamera* _play_camera;

// �e��I�u�W�F�N�g�̃��X�g
protected: std::list<CharaBase*> *_all_chara_list;
//protected: SkillList* _skill_list;
protected: std::list<MagicBase*>* _magic_list;
protected: ShadowObjectList* _shadow_list;

// �����A�C�e��
protected: HaveUseItemList* _use_item_list;
protected: HaveEquipItemList* _equip_item_list;

// �G�Ɏg�����Ƃ��Ă���X�L��
// TODO NPC��AI�݂̂Ŏg�p���Ă���B���L�̎g�p���X�L���ő�ւł���悤�ɂ�����
protected: SkillAttack* _set_attack_skill;

// ���ݎg�p���̃X�L��
protected: SkillBase* _set_now_skill;
//protected: std::unique_ptr<SkillBase> _set_now_skill;

// �X�L���g�p���ɂ��^�[�Q�b�g�ǔ�
protected: CharaBase* _skill_target_obj;
private: int _skill_chain_num;

// �����蔻��
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
// �L�����N�^�[�����������ۂ̏���
//-----------------------------------------------------------
protected: virtual void charaRevival();
public: void allActionCancel();
//-----------------------------------------------------------
// �L�����N�^�[�̈ړ��̍X�V�������s��
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

//	�r�����̕����ύX��ʒu�̍X�V
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
// �s���Ɋ�����v�f�̊֐�
//-----------------------------------------------------------
public: void setNoControlFrame(int frame_num);

// �U����̃X�L���ȊO�̍s�����\�ɂȂ�܂ł̎��Ԃ��Z�b�g
public: void setAttackFrame(int frame_num);

// ���̃X�L�����g����悤�ɂȂ�܂ł̎��Ԃ��擾
public: void setSkillFrame(int frame_num);

// �r����Ԃ��Z�b�g����
public: void setSpellStatus(int spell_state);

// �r����Ԃ��畜�A����
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
// ��+��ȂǂŎg�������Ԃ��擾
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
//	�^�[�Q�b�g�̕������擾����
//-----------------------------------------------------------
private: double getTargetAngleSkill();
private: void resetTargetChara();
protected: double getTargetAngle(double x1, double y1, double x2, double y2);



// �}�b�v�ړ��ɂ�鏉���ʒu�ݒ�
public: virtual void setCharaMapPoint(double point_x, double point_y);
};
