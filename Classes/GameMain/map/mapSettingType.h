#pragma once

enum class mapSettingType{

	_no_type = 0,

	normal = 1,				// 壁オブジェクト配置
	room_center = 2,		// 部屋：基準マス
	room_normal = 3,		// 部屋：通常マス
	road = 4,				// 道
	frame_obj = 5,			// 外枠壁オブジェクト配置
	randam_item_box = 6,		// アイテム箱

	_enum_end,

};