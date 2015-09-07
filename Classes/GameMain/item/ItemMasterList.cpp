#include "ItemMasterList.h"

#include <filesystem>
#include <algorithm> // for_each


// weapon
#include "equip_item/weapon/sword/WeaponSwordBase.h"
#include "equip_item/weapon/sheath/WeaponSheathBase.h"
#include "equip_item/weapon/rapier/WeaponRapierBase.h"

// use
#include "use_item/UseItem.h"
//#include "use_item/hp_heal/TestHpHeal.h"

#include "../../Random.h"

// �e�A�C�e���̃p�X���X�g
unordered_map<itemDetailType, string> ItemMasterList::_path_list;
// �A�C�e��������Q�Ɨp
unordered_map<string, ItemLoadOnlyMaterial*> ItemMasterList::_item_master_list;
// ���A�x�A�A�C�e��������Q��
unordered_map<int, unordered_map<string, ItemLoadOnlyMaterial*>> ItemMasterList::_item_master_rate_list;
// �A�C�e����ށA�A�C�e��������
unordered_map<itemBaseType, unordered_map<string, ItemLoadOnlyMaterial*>> ItemMasterList::_item_master_type_list;
// �A�C�e���ڍ׎�ށA�A�C�e��������
unordered_map<itemDetailType, unordered_map<string, ItemLoadOnlyMaterial*>> ItemMasterList::_item_master_detail_list;

// �ǂݍ��ݎ��̃A�C�e���X�e�[�^�X����
unordered_map<int, mainStateType> ItemMasterList::_load_equip_state_list;	// ����
unordered_map<int, mainStateType> ItemMasterList::_load_use_state_list;		//���Օi 

// �ǂݍ��ݍςݔ���
bool ItemMasterList::_load_flag = false;

itemDetailType ItemMasterList::_load_item_type = itemDetailType::_no_type;

void ItemMasterList::loadItemList() {
	if (ItemMasterList::_load_flag == true) {
		return;
	}
	// �����Ɂw/�x����ƁA�����f�B���N�g���݂̂ɂȂ�̂Œ���
	ItemMasterList::_path_list[itemDetailType::sword] = "data/item/equip/weapon/sword";
	ItemMasterList::_path_list[itemDetailType::rapier] = "data/item/equip/weapon/rapier";
	ItemMasterList::_path_list[itemDetailType::sheath] = "data/item/equip/weapon/sheath";

	ItemMasterList::_path_list[itemDetailType::potion] = "data/item/use/potion/";
	ItemMasterList::_path_list[itemDetailType::food] = "data/item/use/food/";
	// �A�C�e���̃X�e�[�^�X�ǂݍ��ݏ���

	// �����A�C�e����{�X�e�[�^�X -----------------------------------

	ItemMasterList::_load_equip_state_list[0] = mainStateType::_no_type; //�A�C�e�����Ȃ̂ŉ������Ȃ�
	ItemMasterList::_load_equip_state_list[1] = mainStateType::_no_type; //�A�C�e��ID�Ȃ̂ŉ������Ȃ�
	ItemMasterList::_load_equip_state_list[2] = mainStateType::_no_type; //���A�x�Ȃ̂ŉ������Ȃ�
	ItemMasterList::_load_equip_state_list[3] = mainStateType::atk;
	ItemMasterList::_load_equip_state_list[4] = mainStateType::def;
	ItemMasterList::_load_equip_state_list[5] = mainStateType::magic;
	ItemMasterList::_load_equip_state_list[6] = mainStateType::mdef;
	ItemMasterList::_load_equip_state_list[7] = mainStateType::cc;

	// ����A�C�e����{�X�e�[�^�X -----------------------------------

	ItemMasterList::_load_use_state_list[0] = mainStateType::_no_type; //�A�C�e�����Ȃ̂ŉ������Ȃ�
	ItemMasterList::_load_use_state_list[1] = mainStateType::_no_type; //�A�C�e��ID�Ȃ̂ŉ������Ȃ�
	ItemMasterList::_load_use_state_list[2] = mainStateType::_no_type; //���A�x�Ȃ̂ŉ������Ȃ�
	ItemMasterList::_load_use_state_list[3] = mainStateType::_no_type; //���ʎ��ԂȂ̂ŉ������Ȃ�
	ItemMasterList::_load_use_state_list[4] = mainStateType::_no_type; //�H�����ԂȂ̂ŉ������Ȃ�

	//�񕜌���
	ItemMasterList::_load_use_state_list[5] = mainStateType::hp;
	ItemMasterList::_load_use_state_list[6] = mainStateType::sp;
	ItemMasterList::_load_use_state_list[7] = mainStateType::honey;
	ItemMasterList::_load_use_state_list[8] = mainStateType::excitation;
	ItemMasterList::_load_use_state_list[9] = mainStateType::satiety;

	// �␳����
	ItemMasterList::_load_use_state_list[10] = mainStateType::hp;
	ItemMasterList::_load_use_state_list[11] = mainStateType::sp;
	ItemMasterList::_load_use_state_list[12] = mainStateType::atk;
	ItemMasterList::_load_use_state_list[13] = mainStateType::def;
	ItemMasterList::_load_use_state_list[14] = mainStateType::magic;
	ItemMasterList::_load_use_state_list[15] = mainStateType::mdef;
	ItemMasterList::_load_use_state_list[16] = mainStateType::cc;

	ItemMasterList::_load_use_state_list[17] = mainStateType::str;
	ItemMasterList::_load_use_state_list[18] = mainStateType::dex;
	ItemMasterList::_load_use_state_list[19] = mainStateType::intelligence;
	ItemMasterList::_load_use_state_list[20] = mainStateType::luk;

	// �L�����N�^�[��b�X�e�[�^�X
//	ItemMasterList::_load_equip_state_list[1] = mainStateType::str;
//	ItemMasterList::_load_equip_state_list[1] = mainStateType::dex;
//	ItemMasterList::_load_equip_state_list[1] = mainStateType::intelligence;
//	ItemMasterList::_load_equip_state_list[1] = mainStateType::luk;

	// �ǂݍ��݈ꗗ����A�S�ẴA�C�e�������[�h����
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
				// �t�@�C���Ȃ牽�����Ȃ�
				//cout << "file: " << p.filename() << endl;
				//file_name = p.filename();
			}
			else if (sys::is_directory(path)) {
				// �f�B���N�g���̏ꍇ�A�ǂݍ��ݏ������s��
				string dir_path = path.string();
				string dir_name = path.filename();
				loadTypeAndPath(ItemMasterList::_load_item_type, dir_path, dir_name);
			}

			int hoge = 1;
		});
	}
}

void ItemMasterList::loadTypeAndPath(itemDetailType item_type, string dir_path, string item_name) {

	// item_type�ɂ���Ĕ����ɏ������ς��̂ŁA�ʂɊ֐�������ă��[�h����
	switch (item_type) {
	case itemDetailType::sword :
	case itemDetailType::sheath:
	case itemDetailType::rapier :
		ItemMasterList::loadTypeNormalEquip(item_type, dir_path, item_name);
		break;
	case itemDetailType::potion:
	case itemDetailType::food:
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
	
	int item_rare = 0;	// ���A�x
	int count = 0;		// ���[�v��

	ItemLoadOnlyMaterial* equip_obj = new ItemLoadOnlyMaterial();
	equip_obj->_item_type = item_type;
	while (getline(load_data, load_str)) {
		string hoge = load_str;
		switch (count) {
		case 0:
			// ���O�ݒ�
			equip_obj->_item_name = load_str;
			break;
		case 1:
			item_id = load_str;
			equip_obj->_item_id = item_id;
			break;
		case 2:
			item_rare = stoi(load_str);
			break;
		default:
			if (ItemMasterList::_load_equip_state_list[count] != mainStateType::_no_type &&
				ItemMasterList::_load_equip_state_list[count] != mainStateType::_enum_end) {

				mainStateType state_type = ItemMasterList::_load_equip_state_list[count];
				// �X�e�[�^�X�ǂݍ���
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

	int item_rare = 0;	// ���A�x
	int count = 0;		// ���[�v��

	ItemLoadOnlyMaterial* item_material_obj = new ItemLoadOnlyMaterial();
	item_material_obj->_item_type = item_type;
	while (getline(load_data, load_str)) {
		string hoge = load_str;
		switch (count) {
		case 0:
			// ���O�ݒ�
			item_material_obj->_item_name = load_str;
			break;
		case 1:
			// �A�C�e��ID
			item_id = load_str;
			item_material_obj->_item_id = item_id;
			break;
		case 2:
			// ���A�x
			item_rare = stoi(load_str);
			break;
		case 3:
			// ���ʎ���
			item_material_obj->_effect_frame = stoi(load_str);
			if (item_material_obj->_effect_frame < 1) {
				item_material_obj->_effect_frame = 1;
			}
			break;
		case 4:
			// �H������ ��TODO������
			
			break;
		default:
			if (ItemMasterList::_load_use_state_list[count] != mainStateType::_no_type &&
				ItemMasterList::_load_use_state_list[count] != mainStateType::_enum_end) {

				mainStateType state_type = ItemMasterList::_load_use_state_list[count];
				if (count <= 9) {
					// �񕜗p�X�e�[�^�X�ǂݍ���
					item_material_obj->setStateData(state_type, stoi(load_str));
				} else {
					// �␳�p�X�e�[�^�X�ǂݍ���
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

ItemBase* ItemMasterList::getItemObjToRateRandom(int rate_num) {
	Random* rand_obj = new Random();
	auto item_master_list = ItemMasterList::_item_master_rate_list[rate_num];
	int item_num = item_master_list.size();
	int item_rand_num = rand_obj->getRandNum(item_num - 1);
	int item_count = 0;
	

	ItemLoadOnlyMaterial* load_item = nullptr;
	for (auto item_material : item_master_list) {
		if (item_count >= item_rand_num) {
			load_item = ItemMasterList::_item_master_list[item_material.second->_item_id];
			break;
		}
		item_count++;
	}
	if (load_item == nullptr) {
		return nullptr;
	}
	
	return ItemMasterList::ItemMaterialToItemBase(load_item);
}
ItemBase* ItemMasterList::ItemMaterialToItemBase(ItemLoadOnlyMaterial* load_item) {
	if (load_item == nullptr) {
		return nullptr;
	}
	WeaponSwordBase* sword_obj = new WeaponSwordBase();
	WeaponSheathBase* sheath_obj = new WeaponSheathBase();
	WeaponRapierBase* rapier_obj = new WeaponRapierBase();
	UseItem* use_item_obj = new UseItem();
	

	switch (load_item->_item_type) {
	case itemDetailType::sword:

		sword_obj->setItemName(load_item->_item_name);
		sword_obj->setStateData(load_item->_default_state);
		return sword_obj;
		break;
	case itemDetailType::sheath:

		sheath_obj->setItemName(load_item->_item_name);
		sheath_obj->setStateData(load_item->_default_state);
		return sheath_obj;
		break;
	case itemDetailType::rapier:

		rapier_obj->setItemName(load_item->_item_name);
		rapier_obj->setStateData(load_item->_default_state);
		return rapier_obj;
		break;
	case itemDetailType::potion:
		// @TODO test
		use_item_obj->setItemName(load_item->_item_name);
		use_item_obj->setUseItemId(load_item->_item_id);
		use_item_obj->setStateData(load_item->_default_state);
		use_item_obj->setCorrectStateData(load_item->_correct_state);
		use_item_obj->setHaveItemType(haveItemType::portion);
		use_item_obj->setEffectFrame(load_item->_effect_frame);
		//this->_effect_frame
		return use_item_obj;

		break;
	case itemDetailType::food:
		use_item_obj->setItemName(load_item->_item_name);
		use_item_obj->setUseItemId(load_item->_item_id);
		use_item_obj->setStateData(load_item->_default_state);
		use_item_obj->setCorrectStateData(load_item->_correct_state);
		use_item_obj->setHaveItemType(haveItemType::food);
		use_item_obj->setEffectFrame(load_item->_effect_frame);
		//this->_effect_frame
		return use_item_obj;
		break;
	}
	return nullptr;
}