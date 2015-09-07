#pragma once

#include <unordered_map>
#include "../item/equip_item/weapon/weaponType.h"

using namespace std;
class SkillMove;
class SkillAttackGroup;
class CharaBase;

class SkillBase {
// setting skill data ---------------------------------------
protected: int _use_sp = 0;
protected: int _use_cc = 0;
protected: string _skill_id = "";
protected: string _skill_name = "no name";

// false = リストに表示されない = ショートカット設定不可能
protected: bool _ui_draw_flag = true; 
//-----------------------------------------------------------

//-----------------------------------
//	_effectType(attack not use)
//	0:player_one
//	1:player_area_of_effect
//	2:enemy_one
//	3:enemy_area_of_effect
//	4:select_area_of_effect
//-----------------------------------
//		protected int _effect_type;

//-----------------------------------
//	[add angle, 1frame speed, junp, frame num]
//-----------------------------------

//		List<SkillMove> _skill_move_list = new List<SkillMove>();
protected: std::unordered_map<int, SkillMove*> _skill_move_list;

protected: int _skill_move_max = 0;
protected: int _skill_move_count = 0;
protected: int _move_frame = 0;

protected: std::unordered_map<int, SkillAttackGroup*> _skill_attack_list;
protected: int _skill_attack_max = 0;
protected: int _skill_attack_count = 0;
protected: int _attack_frame = 0;

protected: CharaBase* _use_chara_obj;
protected: std::list<CharaBase*> *_all_chara_list;
protected: std::list<CharaBase*> _hitcheck_chara_list;

// private int _skill_attack_frame = 0;
// use skill to in air?
protected: bool _in_air_flag = false;
// skill end?
protected: bool _delete_flag = false;

// 連続スキル回数数えるかフラグ
protected: bool _chain_count_flag = true;

// スキルが使える装備状態
//protected: std::list<weaponType> _main_weapon_list;
//protected: std::list<weaponType> _sub_weapon_list;
protected: std::unordered_map<weaponType, weaponType> _main_weapon_list;
protected: std::unordered_map<weaponType, weaponType> _sub_weapon_list;
//-------------------------------------------------------------------

public: SkillBase(CharaBase* use_chara_obj, std::list<CharaBase*>* all_chara_list);
public: ~SkillBase();
public: virtual void skillInit();
public: virtual void skillExtendInit();
protected: void setSkillAttackGroup(SkillAttackGroup* skill_attack_obj);
protected: void setSkillMove(SkillMove* skill_move_obj);
public: virtual void Update();
protected: virtual bool updateSkillEffect();
protected: virtual void attackHitEffect(CharaBase* check_chara_obj);
private: bool updateSkillMove();
private: void moveCheck();
public: void setDeleteFlag();
public: bool getDeleteFlag();
public: bool getInAirFlag();
public: int getUseSp();
public: int getUseCc();
public: bool checkWeaponType();
public: virtual bool checkExtendSkillUse();
public: bool getChainCountFlag();
public: string getSkillId();
public: string getSkillName();

public: bool getUiDrawFlag();
};