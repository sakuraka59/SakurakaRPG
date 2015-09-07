#include "haveItemType.h"
#pragma execution_character_set("utf-8")
std::string _getHaveItemTypeName(haveItemType item_type) {
	std::string type_name = "‚È‚È‚µ‚Ìƒ^ƒCƒv";
	switch (item_type) {
	case haveItemType::weapon:
		type_name = "‚Ô‚«";
		break;
	case haveItemType::armour:
		type_name = "‚Ó‚­";
		break;
	case haveItemType::portion:
		type_name = "‚­‚·‚è";
		break;
	case haveItemType::food:
		type_name = "‚½‚×‚à‚Ì";
		break;
	case haveItemType::etc:
		type_name = "‚»‚Ì‚½";
		break;

	}

	return type_name;
}