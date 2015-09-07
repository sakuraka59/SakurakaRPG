//-------------------------------------------------------------------
//	スキル情報一覧
//	各キャラクターごとに保持する
//	スキルのIDはクラス名となるため、スキル作成時に同一クラス作成禁止
//-------------------------------------------------------------------
#pragma once
#include <map>
#include <list>

using namespace std;

class CharaBase;
class SkillBase;

// スキル
// スキルタイプ
enum class skillType {
	_no_type = -1,

	// 攻撃スキル------

	sword,			// 片手剣
	rapier,			// 細剣
	saver,			// 曲剣


	sword_sheath,	// 片手剣 + 鞘

	magic_normal,	// 無属性魔法

	_enum_end,
};
class SkillList {
private: CharaBase* _chara_obj;

private: map<string, SkillBase*> _skill_list;		// IDごとスキル一覧
private: map<skillType, map<string, SkillBase*>> _skill_type_list;	// Type → IDごとスキル一覧

public: SkillList(CharaBase* chara_obj, list<CharaBase*>* all_chara_list);

// スキルの一覧初期化準備
private: void setSkillListInit(SkillBase* skill_obj, skillType skill_type);

// スキルオブジェクトの取得
public: SkillBase* getSkillObj(string skill_id);

// スキル一覧の取得
public: map<string, SkillBase*> getSkillObjList(skillType skill_type);
		
// タイプごと、スキル一覧の取得
public: map<skillType, map<string, SkillBase*>> getSkillTypeObjList();
};