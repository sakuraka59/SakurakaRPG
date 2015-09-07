#include "haveItemType.h"
#pragma execution_character_set("utf-8")
std::string _getHaveItemTypeName(haveItemType item_type) {
	std::string type_name = "�ȂȂ��̃^�C�v";
	switch (item_type) {
	case haveItemType::weapon:
		type_name = "�Ԃ�";
		break;
	case haveItemType::armour:
		type_name = "�ӂ�";
		break;
	case haveItemType::portion:
		type_name = "������";
		break;
	case haveItemType::food:
		type_name = "���ׂ���";
		break;
	case haveItemType::etc:
		type_name = "���̂�";
		break;

	}

	return type_name;
}