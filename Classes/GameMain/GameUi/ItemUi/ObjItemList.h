#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"

class HaveUseItemList;
class HaveEquipItemList;

using namespace cocos2d;
class ObjItemList : public RenderObject {
protected: HaveUseItemList* _use_item_list;
protected: HaveEquipItemList* _equip_item_list;
private: RenderObject* _type_bg_render_obj;

// ƒAƒCƒeƒ€‚ÌŽí—Þˆê——
private: int _item_type_num = 0;
private: string _test_label;
private: LabelTTF* _label_obj;

public: ObjItemList(HaveUseItemList* use_item_list, HaveEquipItemList* equip_item_list);
private: RenderObject* getBgRenderObj();
public: void openItemListInit();
};


