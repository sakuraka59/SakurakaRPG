#pragma once
#include "../skill_type/SkillAttack.h"

using namespace std;

class OneHandBase : public SkillAttack {
public: OneHandBase(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);

// ˆÈ‰ºƒeƒ“ƒvƒŒ[ƒg“®ì ---------------------------------------------
// a‚èUŒ‚Œn --------------------------------------------------

// ¶‰º‚©‚ç‰Eã‚Ö
public: void slashTemplate1(int attack_range, int attack_speed, SkillMove* set_move = nullptr);

// ¶‰º‚©‚ç‰Eã‚ÖØ‚è•¥‚¢
public: void slashTemplate2(int attack_range, int attack_speed, SkillMove* set_move = nullptr);

// ‰Eã‚©‚ç¶‰º‚ÖŒU¾a‚è
public: void slashTemplate3(int attack_range, int attack_speed, SkillMove* set_move = nullptr);

// “Ë‚«UŒ‚Œn ----------------------------------------------------

// ³–Ê‚Ö“Ë‚«UŒ‚
public: void ThrustTemplate1(int attack_range, int attack_speed, int end_attack_frame, SkillMove* set_move = nullptr);
};