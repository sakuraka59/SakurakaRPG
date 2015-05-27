#pragma once

#include <unordered_map>		// ハッシュテーブル
#include "../HaveItemList.h"
#include "useItemId.h"

class ItemBase;

class HaveUseItemList : public HaveItemList
{
protected: std::unordered_map<useItemId, ItemBase*> _item_list;

public: HaveUseItemList(CharaBase* chara_obj);
public: bool itemUse(useItemId item_id);
};