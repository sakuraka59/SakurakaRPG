#pragma once
#include "cocos2d.h"
#include "../../../RenderObject.h"

class HaveUseItemList;
class HaveEquipItemList;
class ItemBase;
class EquipItem;
class UseItem;

enum class haveItemType;
enum class equipType;
enum class useItemId;

using namespace cocos2d;
using namespace std;

class ObjItemList : public RenderObject {

protected: const int _TEXT_LINE_HEIGHT = 30;
protected: const int _FONT_SIZE = 20;
protected: const int _CURSOR_DELAY_TIME = 10;
protected: const int _BG_WIDTH = 200;
protected: const int _LINE_WIDTH = 5;

/*
protected: HaveUseItemList* _use_item_list;
protected: HaveEquipItemList* _equip_item_list;
*/

protected: bool _open_only_flag = false;
protected: HaveEquipItemList* _equip_item_list;
protected: HaveUseItemList* _use_item_list;
protected: unordered_map<haveItemType, unordered_map<int, EquipItem*>>* _equip_item_list_detail;
protected: unordered_map<haveItemType, unordered_map<string, UseItem*>>* _use_item_list_detail;


protected: unordered_map<haveItemType, unordered_map<EquipItem*, RenderObject*>> _equip_item_flag_list;
protected: unordered_map<equipType, EquipItem*> _equip_item_obj_list;

protected: int _controll_type = 0; // 0 : �A�C�e����ވꗗ		1 : �A�C�e���ڍ׈ꗗ
protected: int _cursor_delay = 0;



// �A�C�e���̎�ވꗗ
protected: RenderObject* _type_bg_render_obj;
protected: int _item_type_num = 0;
protected: int _item_type_cursor = 0;

protected: string _type_label;
protected: RenderObject* _type_label_obj;
protected: unordered_map<int, haveItemType> _type_list;

// �A�C�e���̏ڍ׈ꗗ
protected: RenderObject* _detail_bg_render_obj;
protected: unordered_map<haveItemType, RenderObject*> _item_detail_list;
protected: unordered_map<haveItemType, int> _item_detail_num_list;
protected: string _detail_label = "";
protected: RenderObject* _detail_label_obj;

protected: haveItemType _open_detail_type;
protected: int _item_detail_num = 0;
protected: int _item_detail_cursor = 0;
protected: unordered_map<haveItemType, unordered_map<int, ItemBase*>> _detail_item_list;

//--------------------------------------------------------------------------------------------

// �I�u�W�F�N�g���׎��Ɏg�p����f�[�^
protected: unordered_map<haveItemType, unordered_map<int, ItemBase*>> _obj_item_list; // �A�C�e���ꗗ
protected: unordered_map<haveItemType, RenderObject*> _obj_item_detail_list;
protected: unordered_map<haveItemType, int> _obj_item_detail_num_list;

protected: string _search_obj_type_label;
protected: RenderObject* _search_obj_type_label_obj;
protected: unordered_map<int, haveItemType> _search_obj_type_list;

// �A�C�e���̏ڍ׈ꗗ
/*
private: unordered_map<haveItemType, RenderObject*> _search_obj_item_detail_list;
private: unordered_map<haveItemType, int> _search_obj_item_detail_num_list;
private: string _search_obj_detail_label = "";
private: RenderObject* _search_obj_detail_label_obj;
*/

public: ObjItemList();


public: void setItemList(HaveEquipItemList* equip_item_list, HaveUseItemList* use_item_list);
void ObjItemList::setItemListData(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* equip_item_type_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>>* use_item_type_list
);
public: virtual void setBackGround();
protected: virtual RenderObject* getBgRenderObj();
public: void initCursorPosition();

public: void setOnlyFlag(bool open_only_flag);	// �v���C���[�݂̂̕\�����ǂ����̃t���O���Z�b�g

// �ꗗ�J��
public: void openItemListInit();	// �����̏����i�̂�
//public: void openItemListInit(unordered_map<haveItemType, unordered_map<int, ItemBase*>> search_item_list);	//���ׂĂ�I�u�W�F�N�g�܂߂�
private: void openItemListDetail(
	unordered_map<haveItemType, unordered_map<int, EquipItem*>>* equip_item_type_list,
	unordered_map<haveItemType, unordered_map<string, UseItem*>>* use_item_type_list
);

// �`��̏������n
protected: void openItemDetailListInit(haveItemType item_type);
protected: void openEquipItemDetailListInit(haveItemType item_type);
protected: void openUseItemDetailListInit(haveItemType item_type);
protected: string getItemTypeName(haveItemType item_type);
protected: void openItemDetailInit(haveItemType item_type);
protected: void resetItemTypeList();

// �X�V�����n
public: void Update();
protected: virtual void UpdateItemType();
protected: virtual void UpdateItemDetail();

protected: void useItemDrawUpdate(haveItemType item_type, ItemBase* item_obj);
protected: void useItemDrawUpdateToEquip(haveItemType item_type, EquipItem* item_obj);
protected: void useItemDrawUpdateToUse(haveItemType item_type, UseItem* item_obj);
public: void closeItemList();

public: void removeEquipItem(EquipItem* remove_item_obj);

		
// �A�C�e����������Ɉڂ����߂̏���
private: ObjItemList* _other_item_list_obj;
public: void setObjItemListObj(ObjItemList* other_item_list_obj);	// �ڂ��O�̉������Ƃ��āA���葤�̃��X�g����ێ�
protected: void transferItemObj();									// �A�C�e���𑊎�ɓn��
//private: void transferItemObjDetail(ItemBase* item_obj);
public: void receiveEquipItemObj(EquipItem* item_obj);				// �A�C�e�����󂯎��i�����A�C�e��
public: void receiveUseItemObj(UseItem* item_obj);					// �A�C�e�����󂯎��i����A�C�e��

private: void removeEquipItemList(EquipItem* item_obj);
private: bool removeUseItemList(UseItem* item_obj);

};