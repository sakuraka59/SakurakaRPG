#pragma once

#include <unordered_map>
#include "../HaveItemList.h"
#include "../haveItemType.h"

using namespace std;

class EquipItem;

class HaveEquipItemList : public HaveItemList
{
protected: unordered_map<int, EquipItem*> _item_list = unordered_map<int, EquipItem*>();
protected: unordered_map<haveItemType, unordered_map<int, EquipItem*>> _item_type_list = unordered_map<haveItemType, unordered_map<int, EquipItem*>>();
private: int _list_index = 0;
public: HaveEquipItemList(CharaBase* chara_obj);
private: int setListToItem(EquipItem* item_obj);
public: bool itemUse(int index);
};