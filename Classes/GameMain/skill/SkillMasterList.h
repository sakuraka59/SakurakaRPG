/*
//-------------------------------------------------------------------
//
//	スキル情報一覧
//	名称が適切じゃないのでSkillListに移行
//
//-------------------------------------------------------------------
#pragma once
#include <map>

using namespace std;

class CharaBase;
class SkillBase;

// スキル
// スキルタイプ
enum class SkillType {
	_no_type = -1,

	// 攻撃スキル------
	
	sword,			// 片手剣
	rapier,			// 細剣


	sword_sheath,	// 片手剣 + 鞘

	_enum_end,
};
class SkillMasterList {
private: CharaBase* _chara_obj;

private: map<string, SkillBase*> _skill_list;		// IDごとスキル一覧
private: map<SkillType, map<string, SkillBase*>> _skill_type_list;	// Type → IDごとスキル一覧

public: SkillMasterList(CharaBase* chara_obj);

// スキルの一覧初期化準備
private: void setSkillListInit(SkillBase* skill_obj);

// スキルオブジェクトの取得
public: SkillBase* getSkillObj(string skill_id);

// スキル一覧の取得
public: map<string, SkillBase*> getSkillObjList(SkillType skill_type);

};
*/