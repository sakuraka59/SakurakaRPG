#pragma once
#include "abnormal_state\abnormalStateType.h"
enum class charaSexualState
{
	normal = 0,

	//	aphrodisiac = abnormalStateType::aphrodisiac,//	›Z–ò
	feel_hot = (int)abnormalStateType::feel_hot,		//	‰ÎÆ‚è
	oestrus = (int)abnormalStateType::oestrus,		//	”­îinot”­îŠú
	extasy = (int)abnormalStateType::extasy,			//	â’¸
	//	sensitive = abnormalStateType::sensitive,	//	•qŠ´iâ’¸Œã‚È‚Ç

	enum_end,
};