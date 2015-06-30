#pragma once

enum class charaActionType
{
	_no_type = -1,

	stand,		// 立ち
	walk,		// 歩き
	dash,		// 走り
	jump,		// ジャンプ
	down,		// キャラクターダウン

	// 以降、攻撃系
	_attack_line,

	_enum_end,

};
