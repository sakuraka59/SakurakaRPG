#pragma once

#include "../ItemBase.h"
#include "../../chara/equipType.h"
#include "../../chara/abnormal_state/abnormalStateType.h"


class EquipItem : public ItemBase
{
protected: std::unordered_map<mainStateType, int> _default_state;
protected: std::unordered_map<abnormalStateType, int> _state_default_list;

protected: equipType _item_equip_type = equipType::_no_type;
protected: bool _equip_flag = false; //装備フラグ

protected: int _list_index = -1;

public: EquipItem();
protected: virtual void setStateInit();
public: void setListIndex(int index);
public: int getListIndex();
public: bool useItem() override;
public: std::unordered_map<mainStateType, int> getItemState();
protected: virtual bool checkExtendEquipItem();	//装備条件拡張

protected: virtual void releaseEquipChain();	// 装備時による他装備解除
public: virtual bool checkEquipRelease();		// 他装備時の装備解除チェック

public: void setEquipFlag();
public: void unsetEquipFlag();
public: bool getEquipFlag();

public: equipType getEquipType();
public: std::unordered_map<abnormalStateType, int> getStateDefaultList();	// 装備時で付与する状態異常

// アイテムロード時のステータス設定用
public: void setStateData(unordered_map<mainStateType, int> default_state);

};
