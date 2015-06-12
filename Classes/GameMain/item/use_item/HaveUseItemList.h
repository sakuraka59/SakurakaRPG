#pragma once

#include <unordered_map>		// ハッシュテーブル
#include "../HaveItemListBase.h"
#include "useItemId.h"
#include "../haveItemType.h"

using namespace std;

class UseItem;

class HaveUseItemList : public HaveItemListBase
{
protected: unordered_map<useItemId, UseItem*> _item_list;
protected: unordered_map<haveItemType, unordered_map<useItemId, UseItem*>> _item_type_list;

public: HaveUseItemList(CharaBase* chara_obj);
public: void setItem(useItemId item_id, int item_num);

public: bool itemUse(useItemId item_id);
public: unordered_map<haveItemType, unordered_map<useItemId, UseItem*>>* getItemTypeList();
};