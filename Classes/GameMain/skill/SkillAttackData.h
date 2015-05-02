#pragma once

class SkillAttackData {
	//-----------------------------------
	//	_skill_type
	//	[type = 2, angle min, angle max, range min, range max, height_base, height]
	//	[type = 3, none, none, none, none] hit check reset
	//-----------------------------------
protected: int _skill_attack_type;

public: float _check_a_1 = 0;
public: float _check_a_2 = 0;
public: float _check_b_1 = 0;
public: float _check_b_2 = 0;
public: float _attack_height_base = 0;
public: float _attack_height = 0;

public: SkillAttackData(int type, float check_a1, float check_a2,
	float check_b1, float check_b2,
	float attack_height_base, float attack_height);

public: int getSkillType();
};