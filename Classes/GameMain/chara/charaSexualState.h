#pragma once
#include "abnormal_state\abnormalStateType.h"
enum class charaSexualState
{
	normal = 0,

	//	aphrodisiac = abnormalStateType::aphrodisiac,//	�Z��
	feel_hot = (int)abnormalStateType::feel_hot,		//	�ΏƂ�
	oestrus = (int)abnormalStateType::oestrus,		//	����inot�����
	extasy = (int)abnormalStateType::extasy,			//	�Ⓒ
	//	sensitive = abnormalStateType::sensitive,	//	�q���i�Ⓒ��Ȃ�

	enum_end,
};