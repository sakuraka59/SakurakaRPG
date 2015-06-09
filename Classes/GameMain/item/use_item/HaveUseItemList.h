#pragma once

#include <unordered_map>		// ハッシュテーブル
#include "../HaveItemList.h"
#include "useItemId.h"
#include "../haveItemType.h"

using namespace std;

class ItemBase;

class HaveUseItemList : public HaveItemList
{
protected: unordered_map<useItemId, ItemBase*> _item_list;
protected: unordered_map<haveItemType, unordered_map<useItemId, ItemBase*>> _item_type_list;

public: HaveUseItemList(CharaBase* chara_obj);
public: bool itemUse(useItemId item_id);
};