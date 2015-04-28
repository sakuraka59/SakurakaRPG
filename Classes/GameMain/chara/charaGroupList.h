#ifndef __CHARA_GROUP_LIST__
#define __CHARA_GROUP_LIST__

enum charaGroupList
{
	no_data = 0,
	game_master,	// 誰からもアクティブでターゲットされない
	player,			// プレイヤー限定
	human,			// 種族：人間
	inhabitant,		// 住民（monster含め

	thief,			// 野良盗賊

	monster,		// 魔物すべて


};

#endif //__CHARA_GROUP_LIST__