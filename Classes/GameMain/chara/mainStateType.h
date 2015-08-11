#pragma once
#include <iostream>

// メモ
// 『int』は型名で使えないので、仕方なく略称しない

enum class mainStateType
{
	// drow num to 1/100
	_no_type = 0,

	hp,		//	base and correction to max. now to now_state
	sp,		//	base and correction to max. now to now_state

	// 基本ステータス
	atk,			// 攻撃力
	def,			// 防御力

	magic,			// 魔力
	mdef,			// 対魔力防御

	cc,				// チェインキャパ

	str,			// 筋力
	dex,			// 器用さ
	intelligence,	// 知力
	luk,			// 運



	// セクシャルに関するステータス
	honey,		// 性的な興奮度 10000で最大。
	excitation,	// 快感度 10000で絶頂。


	// 魔法に関するステータス
//	magic_ex_state,		// 魔力励起中かどうか
//	magic_excitation,	// 魔力励起量


	// 各種属性耐性値
	fire,
	aqua,
	ice,
	thunder,

	_enum_end,

};
