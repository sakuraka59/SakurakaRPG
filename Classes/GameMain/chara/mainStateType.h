#pragma once
#include <iostream>

// ����
// �wint�x�͌^���Ŏg���Ȃ��̂ŁA�d���Ȃ����̂��Ȃ�

enum class mainStateType
{
	// drow num to 1/100
	_no_type = 0,

	hp,		//	base and correction to max. now to now_state
	sp,		//	base and correction to max. now to now_state

	// ��{�X�e�[�^�X
	atk,			// �U����
	def,			// �h���

	magic,			// ����
	mdef,			// �Ζ��͖h��

	cc,				// �`�F�C���L���p

	str,			// �ؗ�
	dex,			// ��p��
	intelligence,	// �m��
	luk,			// �^



	// �Z�N�V�����Ɋւ���X�e�[�^�X
	honey,		// ���I�ȋ����x 10000�ōő�B
	excitation,	// �����x 10000�ŐⒸ�B


	// ���@�Ɋւ���X�e�[�^�X
//	magic_ex_state,		// ���͗�N�����ǂ���
//	magic_excitation,	// ���͗�N��


	// �e�푮���ϐ��l
	fire,
	aqua,
	ice,
	thunder,

	_enum_end,

};
