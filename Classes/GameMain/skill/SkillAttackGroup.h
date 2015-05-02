#pragma once
#include <unordered_map>

class SkillAttackData;

class SkillAttackGroup {

private: int _frame_num = 0;
private: std::unordered_map<int, SkillAttackData*> _attack_data_list;

private: int _list_num = 0;

public: SkillAttackGroup(int frame_num);
public: int getFrameNum();
public: void setSkillAttack(int type, float check_a1, float check_a2,
	float check_b1, float check_b2,
	float attack_height_base, float attack_height);

public: SkillAttackData* getSkillAttack(int index);
public: int getSkillSize();
};