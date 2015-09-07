//-------------------------------------------------------------------
//	�X�L�����ꗗ
//	�e�L�����N�^�[���Ƃɕێ�����
//	�X�L����ID�̓N���X���ƂȂ邽�߁A�X�L���쐬���ɓ���N���X�쐬�֎~
//-------------------------------------------------------------------
#pragma once
#include <map>
#include <list>

using namespace std;

class CharaBase;
class SkillBase;

// �X�L��
// �X�L���^�C�v
enum class skillType {
	_no_type = -1,

	// �U���X�L��------

	sword,			// �Ў茕
	rapier,			// �׌�
	saver,			// �Ȍ�


	sword_sheath,	// �Ў茕 + ��

	magic_normal,	// ���������@

	_enum_end,
};
class SkillList {
private: CharaBase* _chara_obj;

private: map<string, SkillBase*> _skill_list;		// ID���ƃX�L���ꗗ
private: map<skillType, map<string, SkillBase*>> _skill_type_list;	// Type �� ID���ƃX�L���ꗗ

public: SkillList(CharaBase* chara_obj, list<CharaBase*>* all_chara_list);

// �X�L���̈ꗗ����������
private: void setSkillListInit(SkillBase* skill_obj, skillType skill_type);

// �X�L���I�u�W�F�N�g�̎擾
public: SkillBase* getSkillObj(string skill_id);

// �X�L���ꗗ�̎擾
public: map<string, SkillBase*> getSkillObjList(skillType skill_type);
		
// �^�C�v���ƁA�X�L���ꗗ�̎擾
public: map<skillType, map<string, SkillBase*>> getSkillTypeObjList();
};