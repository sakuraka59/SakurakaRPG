#pragma once
enum class weaponType {
	no_type = -1,

	// one hand
	no_weapon,		// 未装備
	sword,			// 片手直剣
	saber,			// 片手曲剣
	rapier,			// レイピア

	//two hand
	two_hand_sword,	// 両手剣

	// sub only
	sheath,			// 鞘


	all_weapon,	// 武器種判定用
	enum_end,
};