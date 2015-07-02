#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"

class HaveUseItemList;
class HaveEquipItemList;
class ItemBase;
class EquipItem;
class UseItem;

enum class haveItemType;

using namespace cocos2d;
using namespace std;

class ObjItemList : public RenderObject {

private: const int _TEXT_LINE_HEIGHT = 30;
private: const int _FONT_SIZE = 20;
private: const int _CURSOR_DELAY_TIME = 10;
protected: HaveUseItemList* _use_item_list;
protected: HaveEquipItemList* _equip_item_list;

private: unordered_map<haveItemType, unordered_map<EquipItem*, RenderObject*>> _equip_item_flag_list;

private: int _controll_type = 0; // 0 : アイテム種類一覧		1 : アイテム詳細一覧
private: int _cursor_delay = 0;

// アイテムの種類一覧
private: RenderObject* _type_bg_render_obj;
private: int _item_type_num = 0;
private: int _item_type_cursor = 0;

private: string _type_label;
private: RenderObject* _type_label_obj;
private: unordered_map<int, haveItemType> _type_list;

// アイテムの詳細一覧
private: RenderObject* _detail_bg_render_obj;
private: unordered_map<haveItemType, RenderObject*> _item_detail_list;
private: unordered_map<haveItemType, int> _item_detail_num_list;
private: string _detail_label = "";
private: RenderObject* _detail_label_obj;

private: haveItemType _open_detail_type;
private: int _item_detail_num = 0;
private: int _item_detail_cursor = 0;
private: unordered_map<haveItemType, unordered_map<int, ItemBase*>> _detail_item_list;
//


public: ObjItemList(HaveUseItemList* use_item_list, HaveEquipItemList* equip_item_list);
private: RenderObject* getBgRenderObj();
public: void openItemListInit();
private: void openItemDetailListInit(haveItemType item_type);
private: void openEquipItemDetailListInit(haveItemType item_type);
private: void openUseItemDetailListInit(haveItemType item_type);
private: string getItemTypeName(haveItemType item_type);
private: void openItemDetailInit(haveItemType item_type);
public: void Update();
private: void UpdateItemType();
private: void UpdateItemDetail();

private: void useItemDrawUpdate(haveItemType item_type, ItemBase* item_obj);
private: void useItemDrawUpdateToEquip(haveItemType item_type, EquipItem* item_obj);
private: void useItemDrawUpdateToUse(haveItemType item_type, UseItem* item_obj);
public: void closeItemList();
};


