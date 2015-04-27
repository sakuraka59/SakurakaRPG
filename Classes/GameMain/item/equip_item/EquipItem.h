#ifndef __EQUIP_ITEM__
#define __EQUIP_ITEM__

#include "../ItemBase.h"
#include "../../chara/equipType.h"

class EquipItem : public ItemBase
{
public: std::unordered_map<mainStateType, int> _default_state;
//public: std::unordered_map<abnormalStateType, int> _state_default_list;

protected: equipType _item_type = equipType::no_type;

public: EquipItem(CharaBase* chara_obj);
};

#endif //__EQUIP_ITEM__