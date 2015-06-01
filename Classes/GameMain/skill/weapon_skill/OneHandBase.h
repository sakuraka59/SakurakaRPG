#pragma once
#include "../skill_type/SkillAttack.h"

using namespace std;

class OneHandBase : public SkillAttack {
public: OneHandBase(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);

// �ȉ��e���v���[�g���� ---------------------------------------------
// �a��U���n --------------------------------------------------

// ��������E���
public: void slashTemplate1(int attack_range, int attack_speed, SkillMove* set_move = nullptr);

// ��������E��֐؂蕥��
public: void slashTemplate2(int attack_range, int attack_speed, SkillMove* set_move = nullptr);

// �E�ォ�獶���֌U���a��
public: void slashTemplate3(int attack_range, int attack_speed, SkillMove* set_move = nullptr);

// �˂��U���n ----------------------------------------------------

// ���ʂ֓˂��U��
public: void ThrustTemplate1(int attack_range, int attack_speed, int end_attack_frame, SkillMove* set_move = nullptr);
};