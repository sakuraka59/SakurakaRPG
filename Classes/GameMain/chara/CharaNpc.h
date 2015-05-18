#pragma once

#include "CharaBase.h"
#include <unordered_map>

class SkillList;
enum class aiAction{
	no_type = -1,
	stand,
	move,
	battle,

	enum_end,
};

class CharaNpc : public CharaBase {

private: int _ai_base_count = 0;
private: aiAction _ai_set_action = aiAction::no_type;

private: double _restart_x = 0;
private: double _restart_y = 0;

private: const int _AI_SET_COUNT = 220;
//		int _set_move_angle = 0;

// �^�[�Q�b�g�ɂ��Ȃ��O���[�v
protected: std::list<charaGroupList> _fellow_group_list;

// �^�[�Q�b�g�ɂ���O���[�v�i�^�[�Q�b�g�ɂ��Ȃ��O���[�v�����̏ꍇ�A�������D��j
protected: std::list<charaGroupList> _target_group_list;

	// test to vision
	/*
	private SpriteUV _test_vision_angle_0;
	private SpriteUV _test_vision_angle_1;
	private SpriteUV _test_vision_angle_2;
	*/
// �G�΂����L�����N�^�[���i�퓬����
protected: CharaBase* _target_enemy_chara = nullptr;

// AI�p�ϐ�
private: bool _before_skill_flag = false;

public: CharaNpc(int set_x, int set_y, GameCamera* camera_obj, std::list<CharaBase*> all_chara_list, std::list<MagicBase*> magic_list, ShadowObjectList* shadow_list);
protected: void setGroupList() override;
protected: void mainUpdate() override;
protected: void charaDownMomentDetail() override;
protected: void charaRevival() override;
private: void npcAi();
private: void searchEnemyChara();
private: double getTargetRange(double x1, double y1, double x2, double y2);
private: void battleAi();
};