#pragma once
#include "../../../RenderObject.h"

class HaveUseItemList;
class HaveEquipItemList;
class ObjItemList : public RenderObject {
protected: HaveUseItemList* _use_item_list;
protected: HaveEquipItemList* _equip_item_list;

public: ObjItemList();
};


