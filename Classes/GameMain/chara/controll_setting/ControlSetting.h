#pragma once
#include <unordered_map>
#include "buttonSettingType.h"

using namespace std;

class ControllSettingDetail;
class SkillBase;
class UseItem;
class CharaPlayer;
// �e���@�킲�Ƃ̐ݒ���
class ControllSetting {
	
private: unordered_map<buttonSettingType, ControllSettingDetail*> _setting_list;

public: ControllSetting(CharaPlayer* chara_obj);

// �X�L�����Z�b�g
public: void setControllSettingSkill(buttonSettingType button_type, SkillBase* skill_obj);

// �A�C�e�����Z�b�g
public: void setControllSettingItem(buttonSettingType button_type, UseItem* item_obj);

// �Z�b�g�������e���g�p
public: void useControllButton(buttonSettingType button_type);

// �Z�b�g���e���������i�������j
public: void resetControllButton(buttonSettingType button_type);
};