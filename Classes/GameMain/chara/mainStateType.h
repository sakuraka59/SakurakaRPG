#ifndef __MAIN_STATE_TYPE__
#define __MAIN_STATE_TYPE__
#include <iostream>

enum class mainStateType
{
	// drow num to 1/100
	hp = 0,		//	base and correction to max. now to now_state
	sp,		//	base and correction to max. now to now_state

	// セクシャルに関するステータス
	honey,		// 性的な興奮度 10000で最大。
	excitation,	// 快感度 10000で絶頂。

	// 基本ステータス
	str,		// 筋力
	dex,		// 器用さ

	atk,		// 攻撃力
	def,		// 防御力

	magic,		// 魔力
	mdef,		// 対魔力防御

	cc,			// チェインキャパ

	// 魔法に関するステータス
	magic_ex_state,		// 魔力励起中かどうか
	magic_excitation,	// 魔力励起量


	// 各種属性耐性値
	fire,
	aqua,
	ice,
	thunder,

	main_state_end,

};

#endif