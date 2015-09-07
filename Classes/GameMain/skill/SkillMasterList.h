/*
//-------------------------------------------------------------------
//
//	�X�L�����ꗗ
//	���̂��K�؂���Ȃ��̂�SkillList�Ɉڍs
//
//-------------------------------------------------------------------
#pragma once
#include <map>

using namespace std;

class CharaBase;
class SkillBase;

// �X�L��
// �X�L���^�C�v
enum class SkillType {
	_no_type = -1,

	// �U���X�L��------
	
	sword,			// �Ў茕
	rapier,			// �׌�


	sword_sheath,	// �Ў茕 + ��

	_enum_end,
};
class SkillMasterList {
private: CharaBase* _chara_obj;

private: map<string, SkillBase*> _skill_list;		// ID���ƃX�L���ꗗ
private: map<SkillType, map<string, SkillBase*>> _skill_type_list;	// Type �� ID���ƃX�L���ꗗ

public: SkillMasterList(CharaBase* chara_obj);

// �X�L���̈ꗗ����������
private: void setSkillListInit(SkillBase* skill_obj);

// �X�L���I�u�W�F�N�g�̎擾
public: SkillBase* getSkillObj(string skill_id);

// �X�L���ꗗ�̎擾
public: map<string, SkillBase*> getSkillObjList(SkillType skill_type);

};
*/