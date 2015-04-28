#pragma once

#include "../../RenderObject.h"
#include <unordered_map>		// �n�b�V���e�[�u��
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
protected: std::unordered_map<equipType, EquipItem> _equip_list;

// ���g���������Ă���O���[�v
//	protected List<charaGroupList> _my_group_list = new List<charaGroupList>();

	//	Correction	�␳
protected: double _hit_height = 0;
protected: double _hit_width_half = 0;

protected: double _run_speed_base = 0;		// ��{�ړ����x
protected: double _run_speed = 0;			// �␳���݈ړ����x
protected: double _walk_speed = 0;			// �������x�i���j

//protected: SeedBase _chara_seed;

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
//protected StateList _state_list;

// ���I�Ɋւ����ԁB�R�����g�ł̂ݎg�p���邱��
//protected charaSexualState _sexual_state = charaSexualState.normal;
//protected charaSexualType _sexual_type = charaSexualType.no_type;

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

//protected: GameCamera _play_camera;

// �e��I�u�W�F�N�g�̃��X�g
protected: std::list<CharaBase> _all_chara_list;
//protected SkillList _skill_list;
//protected List<MagicBase> _magic_list;
//protected ShadowObjectList _shadow_list;

// �����A�C�e��
//protected HaveUseItemList _use_item_list;
//protected HaveEquipItemList _equip_item_list;


// �G�Ɏg�����Ƃ��Ă���X�L��
// TODO NPC��AI�݂̂Ŏg�p���Ă���B���L�̎g�p���X�L���ő�ւł���悤�ɂ�����
//protected SkillAttack _set_attack_skill = null;
// ���ݎg�p���̃X�L��
//protected SkillBase _set_now_skill = null;

// �X�L���g�p���ɂ��^�[�Q�b�g�ǔ�
//protected CharaBase _skill_target_obj = null;
private: int _skill_chain_num;


};
