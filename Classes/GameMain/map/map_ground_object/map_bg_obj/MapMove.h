#pragma once
#include "../MapGroundObjectBase.h"

class MapMove : public MapGroundObjectBase {
protected: int _OBJECT_CORRECT_WIDTH = 64;
protected: int _OBJECT_CORRECT_HEIGHT = 64;

private: bool _DRAW_FLAG = false;

public: MapMove(int map_block_x, int map_block_y, int map_move_type);

//public: void Update() override;
//public: void UpdateInit() override;

protected: void actionObjBehavior(CharaBase* chara_obj) override;
};