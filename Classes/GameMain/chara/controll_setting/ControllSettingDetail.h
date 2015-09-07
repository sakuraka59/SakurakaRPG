#pragma once
#include <string>
#include "buttonSettingType.h"

class UseItem;
class SkillBase;
class CharaPlayer;

using namespace std;

enum class settingDetailType {
	_no_type = 0,
	no_set,
	skill,
	item,
	_enum_end,
};
// 各操作ボタンごとの設定
class ControllSettingDetail {
private: settingDetailType _setting_type;

private: CharaPlayer* _chara_obj;
// ボタン押された際に使うオブジェクト
private: UseItem* _item_obj = nullptr;
private: SkillBase* _skill_obj = nullptr;

public: ControllSettingDetail(CharaPlayer* chara_obj);

// スキルをセットする
public: void setSkill(SkillBase* skill_obj);

// アイテムをセットする
public: void setItem(UseItem* item_obj);

// 設定をリセットする
private: void resetObj();

// セットしたものを使用する
public: void useSetObj();

// セットしたスキルを使用する
public: void useSkill();

// セットしたオブジェクトの名前を返す
public: string getObjName();

// セットしたアイテムを使用する
public: void useItem();
};