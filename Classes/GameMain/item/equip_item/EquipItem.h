#pragma once

#include "../ItemBase.h"
#include "../../chara/equipType.h"
#include "../../chara/abnormal_state/abnormalStateType.h"


class EquipItem : public ItemBase
{
protected: std::unordered_map<mainStateType, int> _default_state;
protected: std::unordered_map<abnormalStateType, int> _state_default_list;

protected: equipType _item_equip_type = equipType::_no_type;
protected: bool _equip_flag = false; //�����t���O

protected: int _list_index = -1;

public: EquipItem();
protected: virtual void setStateInit();
public: void setListIndex(int index);
public: int getListIndex();
public: bool useItem() override;
public: std::unordered_map<mainStateType, int> getItemState();
protected: virtual bool checkExtendEquipItem();	//���������g��

protected: virtual void releaseEquipChain();	// �������ɂ�鑼��������
public: virtual bool checkEquipRelease();		// ���������̑��������`�F�b�N

public: void setEquipFlag();
public: void unsetEquipFlag();
public: bool getEquipFlag();

public: equipType getEquipType();
public: std::unordered_map<abnormalStateType, int> getStateDefaultList();	// �������ŕt�^�����Ԉُ�

// �A�C�e�����[�h���̃X�e�[�^�X�ݒ�p
public: void setStateData(unordered_map<mainStateType, int> default_state);

};
