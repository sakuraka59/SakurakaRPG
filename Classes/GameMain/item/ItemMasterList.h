#pragma once
#pragma execution_character_set("utf-8")

#include <unordered_map>
#include "ItemBase.h"
#include "../chara/mainStateType.h"

#include "equip_item\EquipItem.h"
/*
#include "use_item/UseItem.h"
#include "equip_item/EquipItem.h"
*/
using namespace std;

enum class itemBaseType {
	_no_type = 0,
	equip,		// ����
	use,		// ����
	_enum_end,
};
enum class itemCategoryType {
	_no_type = 0,
	// equip -----------
	weapon,		// ����
	clothes,	// ��

	// use -------------
	potion,		// ��
	food,		// �H�ו�
	_enum_end,
};
enum class itemDetailType {
	_no_type = 0,
	// weapon ----------
	// one hand
	sword,		// �Ў茕
	rapier,		// �׌�
	saber,		// �Ў�Ȍ�

	// sub
	sheath,		// ��

	// two hand


	// clothes ---------
	// main
	hat,		// �X�q�A������
	top,		// �g�b�v�i�V���c��u���E�X�n�A�Z��j
	bottom,		// �{�g���i�Y�{���A�X�J�[�g�A�Z���j
	outer,		// �㒅�i�p�[�J�[��W���P�b�g�A�}���g�j
	socks,		// ������
	shoes,		// �C

	bula,		// �u���A�C���i�[�n�L���~�\�[��
	pants,		// �p���c

	// sub
	earrings,	// �C�������O
	bracelet,	// �r�ցA�U��
	ring,		// �w��
	necklace,	// �����
	anklet,		// �������

	// use -------------
	potion,		// ��
	food,		// �H�ו�
	etc,		// ���̑��f�ޓ��̃A�C�e��
	_enum_end,
};

// �ǂݍ��ݕێ��p�A�C�e���N���X
class ItemLoadOnlyMaterial {

public: string _item_name = "";
public: string _item_id = "";
public: itemDetailType _item_type = itemDetailType::_no_type;
// ���ʃf�[�^ -------------------------------------------------------
// ��{�X�e�[�^�X�B�����A�C�e���Ȃ瑕���␳�A����A�C�e���Ȃ�X�e�[�^�X�񕜗p�B
public: unordered_map<mainStateType, int> _default_state;			
public: unordered_map<abnormalStateType, int> _state_default_list;	// ��Ԉُ�p�X�e�[�^�X

// �����A�C�e���p�X�e�[�^�X -----------------------------------------
// ���ɂȂ���

// ����A�C�e���p�X�e�[�^�X -----------------------------------------
public: int _effect_frame = -1;
// �A�C�e���g�p�ɂ���莞�ԃX�e�[�^�X�␳�p
public: unordered_map<mainStateType, int> _correct_state;

// �f�[�^�Z�b�g
public: void setStateData(mainStateType state_type, int state_num) {
	this->_default_state[state_type] = state_num;
}

// ����A�C�e���␳�p�f�[�^�Z�b�g
public: bool setCorrectStateData(mainStateType state_type, int state_num) {
	if (this->_item_type < itemDetailType::potion ||
		this->_item_type >= itemDetailType::_enum_end) {

		return false;
	}
	this->_correct_state[state_type] = state_num;
	return true;
}
};

class ItemMasterList {

// �e�A�C�e���̃p�X���X�g
private: static unordered_map<itemDetailType, string> _path_list;

// �A�C�e��������Q�Ɨp
private: static unordered_map<string, ItemLoadOnlyMaterial*> _item_master_list;

// ���A�x�A�A�C�e��������Q��
private: static unordered_map<int, unordered_map<string, ItemLoadOnlyMaterial*>> _item_master_rate_list;

// �A�C�e����ށA�A�C�e��������
private: static unordered_map<itemBaseType, unordered_map<string, ItemLoadOnlyMaterial*>> _item_master_type_list;

// �A�C�e���ڍ׎�ށA�A�C�e��������
private: static unordered_map<itemDetailType, unordered_map<string, ItemLoadOnlyMaterial*>> _item_master_detail_list;

// �ǂݍ��ݍςݔ���
private: static bool _load_flag;

private: static itemDetailType _load_item_type;

// �X�e�[�^�X�ǂݍ��ݏ���
private: static unordered_map<int, mainStateType> _load_equip_state_list;	// ����
private: static unordered_map<int, mainStateType> _load_use_state_list;		// ���Օi

private: ItemMasterList();

// �t�@�C�����������āA�S�ẴA�C�e���̃I�u�W�F�N�g���쐬����
public: static void loadItemList();
// �ǂݍ��݊�{�֐�
private: static void loadBase();	
// �A�C�e���̎�ނ��Ƃɓ���U�蕪��
private: static void loadTypeAndPath(itemDetailType item_type, string dir_path, string item_name);
//-------------------------------------------------------------------
// �ȉ��t�@�C���ǂݍ��ݏڍ�
//-------------------------------------------------------------------
// �Ў茕�A�׌�
private: static void loadTypeNormalEquip(itemDetailType item_type, string dir_path, string item_name);

// ��
private: static void loadTypeUse(itemDetailType item_type, string dir_path, string item_name);

// �f�[�^�ǂݍ���
private: static ifstream loadItemData(string dir_path, string item_name);

// �e��I�u�W�F�N�g��Ԃ�
public: static ItemBase* getItemObjToMaster(string item_name);

private: static ItemBase* ItemMaterialToItemBase(ItemLoadOnlyMaterial* load_item);
};
