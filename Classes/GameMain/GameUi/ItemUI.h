#pragma once
#include "UiBase.h"
#include <unordered_map>

using namespace std;

enum class haveItemType;

class CharaPlayer;
class ObjItemList;
class SearchObjItemList;
class ItemBase;
class EquipItem;
class UseItem;
class HaveEquipItemList;
class HaveUseItemList;

enum class itemUiControllState {
	_no_type = -1,
	player,
	search_obj,
	_enum_end,
};

using namespace std;

class ItemUi : public UiBase {
private: bool _draw_flag = false;
private: double _draw_alpha = 0;

// UI��ł̑�����
// 0�F���[�U�[���̃A�C�e���ꗗ
// 1�F���ׂ��I�u�W�F�N�g���̃A�C�e���ꗗ
private: itemUiControllState _controll_state = itemUiControllState::player;

private: bool _search_obj_flag = false;
private: CharaPlayer* _player_obj;

private: ObjItemList* _player_item_list_obj;
private: SearchObjItemList* _search_item_list_obj;


//private: unordered_map<haveItemType, unordered_map<int, EquipItem*>>* _search_obj_equip_item_list;
//private: unordered_map<haveItemType, unordered_map<string, UseItem*>>* _search_obj_use_item_list;
private: HaveEquipItemList* _search_obj_equip_item_list;
private: HaveUseItemList* _search_obj_use_item_list;

public: ItemUi();
public: void Init(CharaPlayer* player_obj);

public: void closeItemUi();		// ����
public: void openItemUi();		// ���g�̃A�C�e��UI�̂݊J��
public: void openItemUiToObj();	// �I�u�W�F�N�g����̃A�C�e���擾���Ɏg��

// ���ׂ��I�u�W�F�N�g�̃A�C�e���ꗗ���Z�b�g
public: void setSearchObjItemList(HaveEquipItemList* equip_item_list, HaveUseItemList* use_item_list);

public: void Update();

public: void removeEquipItem(EquipItem* remove_item_obj);
public: void changeControllState(itemUiControllState controll_state);
};