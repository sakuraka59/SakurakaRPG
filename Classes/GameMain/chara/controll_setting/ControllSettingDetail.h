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
// �e����{�^�����Ƃ̐ݒ�
class ControllSettingDetail {
private: settingDetailType _setting_type;

private: CharaPlayer* _chara_obj;
// �{�^�������ꂽ�ۂɎg���I�u�W�F�N�g
private: UseItem* _item_obj = nullptr;
private: SkillBase* _skill_obj = nullptr;

public: ControllSettingDetail(CharaPlayer* chara_obj);

// �X�L�����Z�b�g����
public: void setSkill(SkillBase* skill_obj);

// �A�C�e�����Z�b�g����
public: void setItem(UseItem* item_obj);

// �ݒ�����Z�b�g����
private: void resetObj();

// �Z�b�g�������̂��g�p����
public: void useSetObj();

// �Z�b�g�����X�L�����g�p����
public: void useSkill();

// �Z�b�g�����I�u�W�F�N�g�̖��O��Ԃ�
public: string getObjName();

// �Z�b�g�����A�C�e�����g�p����
public: void useItem();
};