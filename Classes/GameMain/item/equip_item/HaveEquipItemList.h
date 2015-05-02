#pragma once

#include <unordered_map>
#include "../HaveItemList.h"

class EquipItem;

class HaveEquipItemList : HaveItemList
{
protected: std::unordered_map<int, EquipItem*> _item_list = std::unordered_map<int, EquipItem*>();
private: int _list_index = 0;
public: HaveEquipItemList(CharaBase* chara_obj);
private: int setListToItem(EquipItem* item_obj);
public: bool itemUse(int index);
};