#pragma once
enum class charaCommentType {
	_no_type,		// �����Ȃ��ꍇ�����Ԃ�
	chara_attack,
	normal_damage,

	down,			//	HP0�A�_�E����Ԃ�
	normal_revival,	//	�ʏ한�A

	search_box,		// �󔠂Ȃǂ̃A�C�e����������̂𒲂ׂ�

	// sexual ---------------------------------------------------
	feel_hot_normal,//	�ΏƂ�i�ʏ�j
	oestrus_start,	//	�����xMAX�ɂ�锭��t�^�R�����g
	pleasure,		//	�����Ă���ۂ̊�{�R�����g

	extasy,			//	�Ⓒ

	enum_end,
};