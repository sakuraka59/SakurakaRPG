#pragma once
#include "abnormal_state\abnormalStateType.h"
enum class charaSexualState
{
	normal = 0,

	//	aphrodisiac = abnormalStateType::aphrodisiac,//	Z๒
	feel_hot = (int)abnormalStateType::feel_hot,		//	ฮฦ่
	oestrus = (int)abnormalStateType::oestrus,		//	ญ๎inotญ๎๚
	extasy = (int)abnormalStateType::extasy,			//	โธ
	//	sensitive = abnormalStateType::sensitive,	//	qดiโธใศว

	enum_end,
};