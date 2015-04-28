#pragma once

#include "../ItemBase.h"
#include "../../chara/equipType.h"
#include "../../chara/abnormal_state/abnormalStateType.h"


class EquipItem : public ItemBase
{
public: std::unordered_map<mainStateType, int> _default_state;
public: std::unordered_map<abnormalStateType, int> _state_default_list;

protected: equipType _item_type = equipType::no_type;

public: EquipItem(CharaBase* chara_obj);
protected: virtual void setStateInit();
public: bool useItem() override;
public: std::unordered_map<mainStateType, int> getItemState();
protected: virtual bool checkExtendEquipItem();	//装備条件拡張


protected: virtual void releaseEquipChain();	// 装備時による他装備解除
public: virtual bool checkEquipRelease();		// 他装備時の装備解除チェック

public: std::unordered_map<abnormalStateType, int> getStateDefaultList();	// 装備時で付与する状態異常
};
