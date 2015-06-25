#pragma once

#include "cocos2d.h"

using namespace cocos2d;
class MapMoveData : public Ref {
private: int _map_move_type = -1;	// 移動先マップタイプ
private: int _move_block_x = 0;		// 移動先Xマス座標
private: int _move_block_y = 0;		// 移動先Yマス座標
private: int _extend_data_1 = -1;	// 拡張データその1
private: int _extend_data_2 = -1;	// 拡張データその2

// [マップタイプ = 1固定,	移動先Xマス座標,	移動先Yマス座標,	ワールドマップ用X,		ワールドマップ用Y]
// [マップタイプ = 2固定,	移動先Xマス座標,	移動先Yマス座標,	ミニマップ識別ID,		0固定]
// [マップタイプ = 3固定,	0固定,				0固定,				ランダムマップ識別ID,	0固定]

public: MapMoveData(int map_move_type, int move_block_x, int move_block_y, int extend_data_1, int extend_data_2);
public: int getMoveType();		// 移動先マップタイプを返す
public: int getMoveBlockX();	// 移動先Xマス座標を返す
public: int getMoveBlockY();	// 移動先Yマス座標を返す
public: int getExtendData1();	// 拡張データその1を返す
public: int getExtendData2();	// 拡張データその2を返す
};