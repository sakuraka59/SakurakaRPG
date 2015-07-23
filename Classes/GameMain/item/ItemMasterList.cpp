#include "ItemMasterList.h"

#include <filesystem>
#include <algorithm> // for_each


// weapon
#include "equip_item/weapon/sword/WeaponSwordBase.h"
#include "equip_item/weapon/sheath/WeaponSheathBase.h"
#include "equip_item/weapon/rapier/WeaponRapierBase.h"

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

// 読み込み時の装備アイテムステータス順序
unordered_map<int, mainStateType> ItemMasterList::_load_state_list;

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


	// 装備のステータス読み込み順番
	// 装備基本ステータス
	ItemMasterList::_load_state_list[0] = mainStateType::_no_type; //アイテム名なので何もしない
	ItemMasterList::_load_state_list[1] = mainStateType::_no_type; //レア度なので何もしない
	ItemMasterList::_load_state_list[2] = mainStateType::atk;
	ItemMasterList::_load_state_list[3] = mainStateType::def;
	ItemMasterList::_load_state_list[4] = mainStateType::magic;
	ItemMasterList::_load_state_list[5] = mainStateType::mdef;
	ItemMasterList::_load_state_list[6] = mainStateType::cc;

	// キャラクター基礎ステータス
//	ItemMasterList::_load_state_list[1] = mainStateType::str;
//	ItemMasterList::_load_state_list[1] = mainStateType::dex;
//	ItemMasterList::_load_state_list[1] = mainStateType::intelligence;
//	ItemMasterList::_load_state_list[1] = mainStateType::luk;

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
	}
}
void ItemMasterList::loadTypeNormalEquip(itemDetailType item_type, string dir_path, string item_name) {

	ifstream load_data = ItemMasterList::loadItemData(dir_path, item_name);
	string load_str = "";

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
			item_rare = stoi(load_str);
			break;
		default:
			if (ItemMasterList::_load_state_list[count] != mainStateType::_no_type &&
				ItemMasterList::_load_state_list[count] != mainStateType::_enum_end) {

				mainStateType state_type = ItemMasterList::_load_state_list[count];
				// ステータス読み込み
				equip_obj->setEquipStateData(state_type, stoi(load_str));

			}
		}
		count++;
	}

	ItemMasterList::_item_master_list[item_name] = equip_obj;
	ItemMasterList::_item_master_rate_list[item_rare][item_name] = equip_obj;
	ItemMasterList::_item_master_type_list[itemBaseType::equip][item_name] = equip_obj;
	ItemMasterList::_item_master_detail_list[item_type][item_name] = equip_obj;

}
ifstream ItemMasterList::loadItemData(string dir_path, string item_name) {
	string load_file_path = dir_path + "/" + item_name + ".txt";

	ifstream ifs(load_file_path);
	string load_data;
	
	return ifs;
}

ItemBase* ItemMasterList::getItemObjToMaster(string item_name) {
	ItemLoadOnlyMaterial* load_item = ItemMasterList::_item_master_list[item_name];

	return ItemMasterList::ItemMaterialToItemBase(load_item);
}
ItemBase* ItemMasterList::ItemMaterialToItemBase(ItemLoadOnlyMaterial* load_item) {
	if (load_item == nullptr) {
		return nullptr;
	}
	WeaponSwordBase* sword_obj = new WeaponSwordBase();
	WeaponRapierBase* rapier_obj = new WeaponRapierBase();
	switch (load_item->_item_type) {
	case itemDetailType::sword:

		sword_obj->setItemName(load_item->_item_name);
		sword_obj->setStateData(load_item->_default_state);
		return (ItemBase*)sword_obj;
		break;
	case itemDetailType::rapier:

		rapier_obj->setItemName(load_item->_item_name);
		rapier_obj->setStateData(load_item->_default_state);
		return (ItemBase*)rapier_obj;
	}
	return nullptr;
}