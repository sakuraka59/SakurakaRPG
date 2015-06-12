#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"

class HaveUseItemList;
class HaveEquipItemList;

enum class haveItemType;

using namespace cocos2d;
using namespace std;

class ObjItemList : public RenderObject {
protected: HaveUseItemList* _use_item_list;
protected: HaveEquipItemList* _equip_item_list;
private: RenderObject* _type_bg_render_obj;


private: unordered_map<haveItemType, string> _item_detail_list;
// ƒAƒCƒeƒ€‚ÌŽí—Þˆê——
private: int _item_type_num = 0;
private: string _type_label;
private: LabelTTF* _type_label_obj;

public: ObjItemList(HaveUseItemList* use_item_list, HaveEquipItemList* equip_item_list);
private: RenderObject* getBgRenderObj();
public: void openItemListInit();
private: string getItemTypeName(haveItemType item_type);

public: void Update();
};


