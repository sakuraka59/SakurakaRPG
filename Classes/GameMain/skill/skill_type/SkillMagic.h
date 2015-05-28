#pragma once
#include "../SkillBase.h"

using namespace std;

class SkillMagicSpell;
class MagicBase;

class SkillMagic : public SkillBase {

protected: int _starting_magic_frame = 0;		// �����܂łɂ�����t���[����
private: int _spell_frame_time = 0;				// �r�����̌o�߃t���[����

protected: list<SkillMagicSpell*> _spell_list;	// �r���R�����g�̃I�u�W�F�N�g�ꗗ
protected: SkillMagicSpell* _short_spell = nullptr;
private: bool _short_spell_flag = false;

// �X�L���������ɕK�v�Ȃ���
protected: string _magic_active_comment = "";
protected: int	_magic_skill_frame = 0;
protected: int	_magic_attack_frame = 0;
public: MagicBase* _magic_active_obj = nullptr;

public: SkillMagic(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list);
public: void skillInit() override;
//-----------------------------------------------------------
// �ʏ��UPDATE�������ƈړ�������s��Ȃ��֌W�ŁA
// �I�u�W�F�N�g�������ɔj������Ă��܂�
// ���̂��߂Ɉړ��I���t���O����I�u�W�F�N�g��j�󂵂Ȃ��悤�ɃI�[�o�[���C�h����
//-----------------------------------------------------------
public: void Update() override;

protected: bool updateSkillEffect() override;
protected: virtual void skillActiveEffect(CharaBase* check_chara_obj);
};