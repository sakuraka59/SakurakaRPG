#pragma once

#include <unordered_map>
#include "../HaveItemListBase.h"
#include "../haveItemType.h"


using namespace std;

class EquipItem;
class ItemBase;

class ItemLoadOnlyMaterial;

class HaveEquipItemList : public HaveItemListBase
{
protected: unordered_map<int, EquipItem*> _item_list = unordered_map<int, EquipItem*>();
protected: unordered_map<haveItemType, unordered_map<int, EquipItem*>> _item_type_list = unordered_map<haveItemType, unordered_map<int, EquipItem*>>();
private: int _list_index = 0;
public: HaveEquipItemList();
protected: void testItemList() override;
public: int setListToItem(EquipItem* item_obj);
public: void removeListToItem(EquipItem* item_obj);
public: bool itemUse(int index);
public: unordered_map<haveItemType, unordered_map<int, EquipItem*>>* getItemTypeList();

private: ItemBase* ItemMaterialToItemBase(ItemLoadOnlyMaterial* load_item);
};