#ifndef __MAIN_STATE_TYPE__
#define __MAIN_STATE_TYPE__
#include <iostream>

enum class mainStateType
{
	// drow num to 1/100
	hp = 0,		//	base and correction to max. now to now_state
	sp,		//	base and correction to max. now to now_state

	// �Z�N�V�����Ɋւ���X�e�[�^�X
	honey,		// ���I�ȋ����x 10000�ōő�B
	excitation,	// �����x 10000�ŐⒸ�B

	// ��{�X�e�[�^�X
	str,		// �ؗ�
	dex,		// ��p��

	atk,		// �U����
	def,		// �h���

	magic,		// ����
	mdef,		// �Ζ��͖h��

	cc,			// �`�F�C���L���p

	// ���@�Ɋւ���X�e�[�^�X
	magic_ex_state,		// ���͗�N�����ǂ���
	magic_excitation,	// ���͗�N��


	// �e�푮���ϐ��l
	fire,
	aqua,
	ice,
	thunder,

	main_state_end,

};

#endif