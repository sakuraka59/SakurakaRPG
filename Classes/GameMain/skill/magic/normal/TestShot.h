#pragma once
#include "../magic_type/MagicShot.h"
#include "../../SkillMagicSpell.h"

#include "../../../magic/normal/TestMagicShot.h"
#include "../../../magic/effect/slash/SlashUp1.h"

using namespace std;

class TestShot : public MagicShot {
public: TestShot(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : MagicShot(use_chara_obj, all_chara_list)
	{
		// 魔法系の空中発動はNG
		//	this._in_air_flag = true;

		// 装備種制限
		this->_main_weapon_list[weaponType::all_weapon] = weaponType::all_weapon;

		// 消費SP
		this->_use_sp = 50;

		// 詠唱必要時間
		this->_starting_magic_frame = 60;

		// 詠唱中のコメント
		this->_spell_list.push_back(new SkillMagicSpell("試作なる創造の力よ…", 0));
		this->_spell_list.push_back(new SkillMagicSpell("我の力となりて、敵を撃ちぬけ！", 30));

		// 詠唱中のコメント（ショート版）
		this->_short_spell = new SkillMagicSpell("試作なる創造の力よ、敵を撃て！", 0);
		
		// 発動時のコメント
		this->_magic_active_comment = "プロトショット！";

		this->_magic_skill_frame = 60;						// 次のスキルがセットできるようになるまでの時間
		this->_magic_attack_frame = 80;						// 完全に行動が可能になるまでの時間


		//this->_magic_active_obj
		this->_magic_active_obj = new TestMagicShot(this->_use_chara_obj);
		
	}
};