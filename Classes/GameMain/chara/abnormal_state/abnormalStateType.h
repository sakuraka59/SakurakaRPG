#pragma once
enum class abnormalStateType {
	_no_type = 0,
	poison,				//	毒



	
	//-------------------------------
//	sexual,

	// aphrodisiac,		//	媚薬
	feel_hot,			//	火照り
	oestrus,			//	発情（not発情期
	extasy,				//	絶頂
	// sensitive,			//	敏感（絶頂後など
	absent_mindedness,	//	放心
	//*/

	// 持続回復系 ------------------
	hp_effect,
	sp_effect,
	honey_effect,
	excitation_effect,
	satiety_effect,

	// ステータス補正系 ------------------
	hp_correct,
	sp_correct,
	atk_correct,
	def_correct,
	magic_correct,
	mdef_correct,

	_enum_end,
};