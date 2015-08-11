#pragma once
#include "../SkillBase.h"
#include "../../chara/abnormal_state/abnormalStateType.h"

class CharaBase;
class SkillAttackData;

class SkillAttack : public SkillBase {


// npc use only
protected: double _npc_use_range = 10.0;// attack start range

// abnormal state data
protected: abnormalStateType _abnormal_state_type = abnormalStateType::_no_type;
protected: int _state_level = 0;
protected: int _state_rate = 0; // max = 10000

protected: int _attack_reset_count = 0;
private: bool _reset_count_flag = true;

protected: int _set_attack_frame = 0;	// 発動から自由に行動出来るようになるまでのフレーム数
protected: int _set_skill_frame = 0;	// 発動から別スキルへキャンセル出来るようになるまでのフレーム数

public: SkillAttack(CharaBase* use_chara_obj, std::list<CharaBase*> *all_chara_list);
public: void skillExtendInit() override;
protected: bool updateSkillEffect() override;
protected: virtual void attackUpdateEffect();
private: void attackCheck();
private: double getTargetRange(double x1, double y1, double x2, double y2);
private: double getTargetAngle(double x1, double y1, double x2, double y2);
private: bool checkHeightHit(SkillAttackData* skill_attack_data, CharaBase* check_chara_obj);
public: double getNpcUseRange();
};