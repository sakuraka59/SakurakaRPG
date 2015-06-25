// マップ移動管理マネージャー
#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class MapMoveData;

class MapMoveManager : public Ref {

private: static MapMoveData* _map_move_obj;


private: MapMoveManager();

public:
	static void updateInit();
	static bool checkMapMove();
	static void setMapMoveData(MapMoveData* map_move_obj);
	static MapMoveData* getMapMoveData();
};