#pragma once
#include "../SkillBase.h"

using namespace std;

class SkillMagicSpell;
class MagicBase;

class SkillMagic : public SkillBase {

protected: int _starting_magic_frame = 0;		// 発動までにかかるフレーム数
private: int _spell_frame_time = 0;				// 詠唱中の経過フレーム数

protected: list<SkillMagicSpell*> _spell_list;	// 詠唱コメントのオブジェクト一覧
protected: SkillMagicSpell* _short_spell = nullptr;
private: bool _short_spell_flag = false;

// スキル発動時に必要なもの
protected: string _magic_active_comment = "";
protected: int	_magic_skill_frame = 0;
protected: int	_magic_attack_frame = 0;
public: MagicBase* _magic_active_obj = nullptr;

public: SkillMagic(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
public: void skillInit() override;
//-----------------------------------------------------------
// 通常のUPDATE処理だと移動動作を行わない関係で、
// オブジェクトがすぐに破棄されてしまう
// そのために移動終了フラグからオブジェクトを破壊しないようにオーバーライドする
//-----------------------------------------------------------
public: void Update() override;

protected: bool updateSkillEffect() override;
protected: virtual void skillActiveEffect(CharaBase* check_chara_obj);
};