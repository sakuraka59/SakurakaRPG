#pragma once

#include "../../MapObjectBase.h"

class ItemBoxBase : public MapObjectBase {
public: ItemBoxBase(int map_block_x, int map_block_y, GameCamera* camera_obj);
public: void actionObjBehavior(CharaBase* chara_obj) override;
protected: void setItemList() override;
};