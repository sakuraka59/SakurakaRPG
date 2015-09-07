#include "haveItemType.h"
#pragma execution_character_set("utf-8")
std::string _getHaveItemTypeName(haveItemType item_type) {
	std::string type_name = "ななしのタイプ";
	switch (item_type) {
	case haveItemType::weapon:
		type_name = "ぶき";
		break;
	case haveItemType::armour:
		type_name = "ふく";
		break;
	case haveItemType::portion:
		type_name = "くすり";
		break;
	case haveItemType::food:
		type_name = "たべもの";
		break;
	case haveItemType::etc:
		type_name = "そのた";
		break;

	}

	return type_name;
}