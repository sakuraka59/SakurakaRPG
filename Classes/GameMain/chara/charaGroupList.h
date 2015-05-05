#pragma once

enum class charaGroupList
{
	no_data = 0,
	game_master,	// 誰からもアクティブでターゲットされない
	player,			// プレイヤー限定
	human,			// 種族：人間
	inhabitant,		// 住民（monster含め

	thief,			// 野良盗賊

	monster,		// 魔物すべて

	enum_end,
};
