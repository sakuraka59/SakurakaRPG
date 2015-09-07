#pragma once
#include <string>
enum class haveItemType {
	_no_type = 0,

	weapon,		// •Ší
	armour,		// –h‹ï
	
	portion,	// –ò
	food,		// H‚×•¨
	etc,		// ‚»‚Ì‘¼

	_enum_end,
};

std::string _getHaveItemTypeName(haveItemType item_type);