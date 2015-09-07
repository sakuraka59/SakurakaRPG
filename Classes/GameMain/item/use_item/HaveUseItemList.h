#pragma once

#include <unordered_map>		// ハッシュテーブル
#include "../HaveItemListBase.h"
#include "useItemId.h"
#include "../haveItemType.h"

using namespace std;

class UseItem;

class HaveUseItemList : public HaveItemListBase
{
protected: unordered_map<string, UseItem*> _item_list;
protected: unordered_map<haveItemType, unordered_map<string, UseItem*>> _item_type_list;

public: HaveUseItemList();
public: void setItem(UseItem* item_obj, int item_num);
protected: void testItemList() override;

public: bool itemUse(string item_id);
public: unordered_map<haveItemType, unordered_map<string, UseItem*>>* getItemTypeList();
public: unordered_map<string, UseItem* > getItemTypeDetailList(haveItemType item_type);
};