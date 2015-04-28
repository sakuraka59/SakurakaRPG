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
protected: virtual bool checkExtendEquipItem();	//���������g��


protected: virtual void releaseEquipChain();	// �������ɂ�鑼��������
public: virtual bool checkEquipRelease();		// ���������̑��������`�F�b�N

public: std::unordered_map<abnormalStateType, int> getStateDefaultList();	// �������ŕt�^�����Ԉُ�
};
