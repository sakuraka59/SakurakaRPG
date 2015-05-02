#pragma once
enum class charaCommentType {
	no_type,		// 何もない場合これを返す
	chara_attack,
	normal_damage,

	down,			//	HP0、ダウン状態へ
	normal_revival,	//	通常復帰

	// sexual ---------------------------------------------------
	feel_hot_normal,//	火照り（通常）
	oestrus_start,	//	興奮度MAXによる発情付与コメント
	pleasure,		//	感じている際の基本コメント

	extasy,			//	絶頂
};