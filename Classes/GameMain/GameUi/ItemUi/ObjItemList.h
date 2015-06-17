#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"

class HaveUseItemList;
class HaveEquipItemList;

enum class haveItemType;

using namespace cocos2d;
using namespace std;

class ObjItemList : public RenderObject {

private: int _TEXT_LINE_HEIGHT = 30;
private: int _FONT_SIZE = 20;
protected: HaveUseItemList* _use_item_list;
protected: HaveEquipItemList* _equip_item_list;


private: int _controll_type = 0; // 0 : アイテム種類一覧		1 : アイテム詳細一覧

// アイテムの種類一覧
private: RenderObject* _type_bg_render_obj;
private: int _item_type_num = 0;
private: int _item_type_cursor = 0;
private: int _type_cursor_delay = 0;
private: string _type_label;
private: RenderObject* _type_label_obj;
private: unordered_map<int, haveItemType> _type_list;

// アイテムの詳細一覧
private: RenderObject* _detail_bg_render_obj;
private: unordered_map<haveItemType, RenderObject*> _item_detail_list;
private: unordered_map<haveItemType, int> _item_detail_num_list;
private: string _detail_label = "";
private: RenderObject* _detail_label_obj;
private: int _item_detail_num = 0;



public: ObjItemList(HaveUseItemList* use_item_list, HaveEquipItemList* equip_item_list);
private: RenderObject* getBgRenderObj();
public: void openItemListInit();
private: string getItemTypeName(haveItemType item_type);
private: void openItemDetailInit(haveItemType item_type);
public: void Update();
private: void UpdateItemType();
private: void UpdateItemDetail();
};


