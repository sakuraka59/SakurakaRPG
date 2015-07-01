#pragma once
#include "../magic_type/MagicShot.h"
#include "../../SkillMagicSpell.h"

#include "../../../magic/normal/TestMagicShot.h"
#include "../../../magic/effect/slash/SlashUp1.h"

using namespace std;

class TestShot : public MagicShot {
public: TestShot(CharaBase* use_chara_obj, list<CharaBase*>* all_chara_list) : MagicShot(use_chara_obj, all_chara_list)
	{
		// ���@�n�̋󒆔�����NG
		//	this._in_air_flag = true;

		// �����퐧��
		this->_main_weapon_list[weaponType::all_weapon] = weaponType::all_weapon;

		// ����SP
		this->_use_sp = 50;

		// �r���K�v����
		this->_starting_magic_frame = 60;

		// �r�����̃R�����g
		this->_spell_list.push_back(new SkillMagicSpell("����Ȃ�n���̗͂�c", 0));
		this->_spell_list.push_back(new SkillMagicSpell("��̗͂ƂȂ�āA�G�������ʂ��I", 30));

		// �r�����̃R�����g�i�V���[�g�Łj
		this->_short_spell = new SkillMagicSpell("����Ȃ�n���̗͂�A�G�����āI", 0);
		
		// �������̃R�����g
		this->_magic_active_comment = "�v���g�V���b�g�I";

		this->_magic_skill_frame = 60;						// ���̃X�L�����Z�b�g�ł���悤�ɂȂ�܂ł̎���
		this->_magic_attack_frame = 80;						// ���S�ɍs�����\�ɂȂ�܂ł̎���


		//this->_magic_active_obj
		this->_magic_active_obj = new TestMagicShot(this->_use_chara_obj);
		
	}
};