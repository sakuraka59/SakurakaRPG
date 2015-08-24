#pragma once
#include <unordered_map>
#include "buttonSettingType.h"

using namespace std;

class ControllSettingDetail;
class SkillBase;
class UseItem;
class CharaPlayer;
// 各部機種ごとの設定状態
class ControllSetting {
	
private: unordered_map<buttonSettingType, ControllSettingDetail*> _setting_list;

public: ControllSetting(CharaPlayer* chara_obj);

// スキルをセット
public: void setControllSettingSkill(buttonSettingType button_type, SkillBase* skill_obj);

// アイテムをセット
public: void setControllSettingItem(buttonSettingType button_type, UseItem* item_obj);

// セットした内容を使用
public: void useControllButton(buttonSettingType button_type);

// セット内容を初期化（未実装）
public: void resetControllButton(buttonSettingType button_type);
};