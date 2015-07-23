#pragma once
#include <unordered_map>
#include "../../../RenderObject.h"
#include "ObjItemList.h"
/*
using namespace std;

enum class haveItemType;

class RenderObject;
class CharaPlayer;
class ItemBase;
class EquipItem;
class UseItem;
//*/
class SearchObjItemList : public ObjItemList {

public: void setSearchObjItemList(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>> equip_item_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>> use_item_list
);

public: SearchObjItemList();
public: void setBackGround() override;
protected: RenderObject* getBgRenderObj() override;
public: int getDrawWidth();
public: void UpdateItemType() override;
public: void UpdateItemDetail() override;
	/*
private: const int _TEXT_LINE_HEIGHT = 30;
private: const int _FONT_SIZE = 20;
private: const int _CURSOR_DELAY_TIME = 10;
private: const int _BG_WIDTH = 200;
private: const int _LINE_WIDTH = 5;
private: int _cursor_delay = 0;				// �J�[�\���ړ��̃f�B���C�o�ߎ���

private: CharaPlayer* _player_obj;
private: bool _set_flag = false;

//private: unordered_map<haveItemType, unordered_map<int, ItemBase*>> _obj_item_list;
private: unordered_map<haveItemType, unordered_map<int, EquipItem*>> _equip_item_list;
private: unordered_map<haveItemType, unordered_map<string, UseItem*>> _use_item_list;


private: int _controll_type = 0; // 0 : �A�C�e����ވꗗ		1 : �A�C�e���ڍ׈ꗗ
private: int _cursor_delay = 0;

		 // �A�C�e���̎�ވꗗ
private: RenderObject* _type_bg_render_obj;
private: int _item_type_num = 0;
private: int _item_type_cursor = 0;

private: string _type_label;
private: RenderObject* _type_label_obj;
private: unordered_map<int, haveItemType> _type_list;

		 // �A�C�e���̏ڍ׈ꗗ
private: RenderObject* _detail_bg_render_obj;
private: unordered_map<haveItemType, RenderObject*> _item_detail_list;
private: unordered_map<haveItemType, int> _item_detail_num_list;
private: string _detail_label = "";
private: RenderObject* _detail_label_obj;

private: haveItemType _open_detail_type;
private: int _item_detail_num = 0;
private: int _item_detail_cursor = 0;
private: unordered_map<haveItemType, unordered_map<int, ItemBase*>> _detail_item_list;
//--------------------------------------------------------------------------------------------

private: RenderObject* _list_bg_obj;

// ��{����
public: SearchObjItemList();
public: void Init(CharaPlayer* player_obj);
public: void setItemList(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>> equip_item_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>> use_item_list
);


public: void Update();

// �`�搧��
public: void openItemList();
public: void closeItemList();

// �A�C�e������n
private: void getItem();	// �A�C�e����1���肷��
private: void getAllItem();	// �A�C�e����S�ē��肷��

// �w�i����
private: RenderObject* getBgRenderObj();

// �ꗗ�\������
private: void openItemListDetail(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* equip_item_type_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>>* use_item_type_list
);
// ���̑�
public: int getDrawWidth();
*/
};