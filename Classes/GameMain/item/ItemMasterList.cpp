#include "ItemMasterList.h"

#include <filesystem>
#include <algorithm> // for_each


// weapon
#include "equip_item/weapon/sword/WeaponSwordBase.h"
#include "equip_item/weapon/sheath/WeaponSheathBase.h"
#include "equip_item/weapon/rapier/WeaponRapierBase.h"

// use
#include "use_item/hp_heal/TestHpHeal.h"

// 各アイテムのパスリスト
unordered_map<itemDetailType, string> ItemMasterList::_path_list;
// アイテム名から参照用
unordered_map<string, ItemLoadOnlyMaterial*> ItemMasterList::_item_master_list;
// レア度、アイテム名から参照
unordered_map<int, unordered_map<string, ItemLoadOnlyMaterial*>> ItemMasterList::_item_master_rate_list;
// アイテム種類、アイテム名から
unordered_map<itemBaseType, unordered_map<string, ItemLoadOnlyMaterial*>> ItemMasterList::_item_master_type_list;
// アイテム詳細種類、アイテム名から
unordered_map<itemDetailType, unordered_map<string, ItemLoadOnlyMaterial*>> ItemMasterList::_item_master_detail_list;

// 読み込み時のアイテムステータス順序
unordered_map<int, mainStateType> ItemMasterList::_load_equip_state_list;	// 装備
unordered_map<int, mainStateType> ItemMasterList::_load_use_state_list;		//消耗品 

// 読み込み済み判定
bool ItemMasterList::_load_flag = false;

itemDetailType ItemMasterList::_load_item_type = itemDetailType::_no_type;

void ItemMasterList::loadItemList() {
	if (ItemMasterList::_load_flag == true) {
		return;
	}
	// 末尾に『/』つけると、直下ディレクトリのみになるので注意
	ItemMasterList::_path_list[itemDetailType::sword] = "data/item/equip/weapon/sword";
	ItemMasterList::_path_list[itemDetailType::rapier] = "data/item/equip/weapon/rapier";

	ItemMasterList::_path_list[itemDetailType::potion] = "data/item/use/potion/";
	// アイテムのステータス読み込み順番

	// 装備アイテム基本ステータス -----------------------------------

	ItemMasterList::_load_equip_state_list[0] = mainStateType::_no_type; //アイテム名なので何もしない
	ItemMasterList::_load_equip_state_list[1] = mainStateType::_no_type; //アイテムIDなので何もしない
	ItemMasterList::_load_equip_state_list[2] = mainStateType::_no_type; //レア度なので何もしない
	ItemMasterList::_load_equip_state_list[3] = mainStateType::atk;
	ItemMasterList::_load_equip_state_list[4] = mainStateType::def;
	ItemMasterList::_load_equip_state_list[5] = mainStateType::magic;
	ItemMasterList::_load_equip_state_list[6] = mainStateType::mdef;
	ItemMasterList::_load_equip_state_list[7] = mainStateType::cc;

	// 消費アイテム基本ステータス -----------------------------------

	ItemMasterList::_load_use_state_list[0] = mainStateType::_no_type; //アイテム名なので何もしない
	ItemMasterList::_load_use_state_list[1] = mainStateType::_no_type; //アイテムIDなので何もしない
	ItemMasterList::_load_use_state_list[2] = mainStateType::_no_type; //レア度なので何もしない
	ItemMasterList::_load_use_state_list[3] = mainStateType::_no_type; //効果時間なので何もしない

	//回復効果
	ItemMasterList::_load_use_state_list[4] = mainStateType::hp;
	ItemMasterList::_load_use_state_list[5] = mainStateType::sp;
	ItemMasterList::_load_use_state_list[6] = mainStateType::honey;
	ItemMasterList::_load_use_state_list[7] = mainStateType::excitation;

	// 補正効果
	ItemMasterList::_load_use_state_list[8] = mainStateType::hp;
	ItemMasterList::_load_use_state_list[9] = mainStateType::sp;
	ItemMasterList::_load_use_state_list[10] = mainStateType::atk;
	ItemMasterList::_load_use_state_list[11] = mainStateType::def;
	ItemMasterList::_load_use_state_list[12] = mainStateType::magic;
	ItemMasterList::_load_use_state_list[13] = mainStateType::mdef;
	ItemMasterList::_load_use_state_list[14] = mainStateType::cc;

	ItemMasterList::_load_use_state_list[15] = mainStateType::str;
	ItemMasterList::_load_use_state_list[16] = mainStateType::dex;
	ItemMasterList::_load_use_state_list[17] = mainStateType::intelligence;
	ItemMasterList::_load_use_state_list[18] = mainStateType::luk;

	// キャラクター基礎ステータス
//	ItemMasterList::_load_equip_state_list[1] = mainStateType::str;
//	ItemMasterList::_load_equip_state_list[1] = mainStateType::dex;
//	ItemMasterList::_load_equip_state_list[1] = mainStateType::intelligence;
//	ItemMasterList::_load_equip_state_list[1] = mainStateType::luk;

	// 読み込み一覧から、全てのアイテムをロードする
	ItemMasterList::loadBase();
	
	ItemMasterList::_load_flag = true;
}
void ItemMasterList::loadBase() {
	namespace sys = std::tr2::sys;

	for (auto load_data : ItemMasterList::_path_list) {
		ItemMasterList::_load_item_type = load_data.first;
		string load_path = load_data.second;
		sys::path path(load_path);


		std::for_each(sys::directory_iterator(path), sys::directory_iterator(), [](const sys::path& path) {
			string file_name = "";
			if (sys::is_regular_file(path)) {
				// ファイルなら何もしない
				//cout << "file: " << p.filename() << endl;
				//file_name = p.filename();
			}
			else if (sys::is_directory(path)) {
				// ディレクトリの場合、読み込み処理を行う
				string dir_path = path.string();
				string dir_name = path.filename();
				loadTypeAndPath(ItemMasterList::_load_item_type, dir_path, dir_name);
			}

			int hoge = 1;
		});
	}
}

void ItemMasterList::loadTypeAndPath(itemDetailType item_type, string dir_path, string item_name) {

	// item_typeによって微妙に処理が変わるので、個別に関数を作ってロードする
	switch (item_type) {
	case itemDetailType::sword :
	case itemDetailType::rapier :
		ItemMasterList::loadTypeNormalEquip(item_type, dir_path, item_name);
		break;
	case itemDetailType::potion:
		ItemMasterList::loadTypeUse(item_type, dir_path, item_name);
		break;
	}
}
void ItemMasterList::loadTypeNormalEquip(itemDetailType item_type, string dir_path, string item_name) {

	ifstream load_data = ItemMasterList::loadItemData(dir_path, item_name);
	string load_str = "";
	string item_id = "";

	if (load_data.fail()) {
		return;
	}
	
	int item_rare = 0;	// レア度
	int count = 0;		// ループ回数

	ItemLoadOnlyMaterial* equip_obj = new ItemLoadOnlyMaterial();
	equip_obj->_item_type = item_type;
	while (getline(load_data, load_str)) {
		string hoge = load_str;
		switch (count) {
		case 0:
			// 名前設定
			equip_obj->_item_name = load_str;
			break;
		case 1:
			item_id = load_str;
			break;
		case 2:
			item_rare = stoi(load_str);
			break;
		default:
			if (ItemMasterList::_load_equip_state_list[count] != mainStateType::_no_type &&
				ItemMasterList::_load_equip_state_list[count] != mainStateType::_enum_end) {

				mainStateType state_type = ItemMasterList::_load_equip_state_list[count];
				// ステータス読み込み
				equip_obj->setStateData(state_type, stoi(load_str));

			}
		}
		count++;
	}

	ItemMasterList::_item_master_list[item_id] = equip_obj;
	ItemMasterList::_item_master_rate_list[item_rare][item_id] = equip_obj;
	ItemMasterList::_item_master_type_list[itemBaseType::equip][item_id] = equip_obj;
	ItemMasterList::_item_master_detail_list[item_type][item_id] = equip_obj;

}
void ItemMasterList::loadTypeUse(itemDetailType item_type, string dir_path, string item_name) {

	ifstream load_data = ItemMasterList::loadItemData(dir_path, item_name);
	string load_str = "";
	string item_id = "";

	if (load_data.fail()) {
		return;
	}

	int item_rare = 0;	// レア度
	int count = 0;		// ループ回数

	ItemLoadOnlyMaterial* item_material_obj = new ItemLoadOnlyMaterial();
	item_material_obj->_item_type = item_type;
	while (getline(load_data, load_str)) {
		string hoge = load_str;
		switch (count) {
		case 0:
			// 名前設定
			item_material_obj->_item_name = load_str;
			break;
		case 1:
			// アイテムID
			item_id = load_str;
			item_material_obj->_item_id = item_id;
			break;
		case 2:
			// レア度
			item_rare = stoi(load_str);
			break;
		case 3:
			// 効果時間
			item_material_obj->_effect_frame = stoi(load_str);
			if (item_material_obj->_effect_frame < 1) {
				item_material_obj->_effect_frame = 1;
			}
			break;
		default:
			if (ItemMasterList::_load_use_state_list[count] != mainStateType::_no_type &&
				ItemMasterList::_load_use_state_list[count] != mainStateType::_enum_end) {

				mainStateType state_type = ItemMasterList::_load_use_state_list[count];
				if (count <= 7) {
					// 回復用ステータス読み込み
					item_material_obj->setStateData(state_type, stoi(load_str));
				} else {
					// 補正用ステータス読み込み
					item_material_obj->setCorrectStateData(state_type, stoi(load_str));
				}

			}
		}
		count++;
	}

	ItemMasterList::_item_master_list[item_id] = item_material_obj;
	ItemMasterList::_item_master_rate_list[item_rare][item_id] = item_material_obj;
	ItemMasterList::_item_master_type_list[itemBaseType::equip][item_id] = item_material_obj;
	ItemMasterList::_item_master_detail_list[item_type][item_id] = item_material_obj;

}
ifstream ItemMasterList::loadItemData(string dir_path, string item_name) {
	string load_file_path = dir_path + "/" + item_name + ".txt";

	ifstream ifs(load_file_path);
	string load_data;
	
	return ifs;
}

ItemBase* ItemMasterList::getItemObjToMaster(string item_id) {
	ItemLoadOnlyMaterial* load_item = ItemMasterList::_item_master_list[item_id];

	return ItemMasterList::ItemMaterialToItemBase(load_item);
}
ItemBase* ItemMasterList::ItemMaterialToItemBase(ItemLoadOnlyMaterial* load_item) {
	if (load_item == nullptr) {
		return nullptr;
	}
	WeaponSwordBase* sword_obj = new WeaponSwordBase();
	WeaponRapierBase* rapier_obj = new WeaponRapierBase();
	UseItem* potion_obj = new UseItem();
	

	switch (load_item->_item_type) {
	case itemDetailType::sword:

		sword_obj->setItemName(load_item->_item_name);
		sword_obj->setStateData(load_item->_default_state);
		return sword_obj;
		break;
	case itemDetailType::rapier:

		rapier_obj->setItemName(load_item->_item_name);
		rapier_obj->setStateData(load_item->_default_state);
		return rapier_obj;
		break;
	case itemDetailType::potion:
		// @TODO test
		potion_obj->setItemName(load_item->_item_name);
		potion_obj->setUseItemId(load_item->_item_id);
		potion_obj->setStateData(load_item->_default_state);
		potion_obj->setCorrectStateData(load_item->_correct_state);
		potion_obj->setHaveItemType(haveItemType::portion);
		potion_obj->setEffectFrame(load_item->_effect_frame);
		//this->_effect_frame
		return potion_obj;

		break;
	case itemDetailType::food:
		break;
	}
	return nullptr;
}