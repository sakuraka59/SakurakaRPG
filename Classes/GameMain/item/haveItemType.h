#pragma once
#include <string>
enum class haveItemType {
	_no_type = 0,

	weapon,		// ����
	armour,		// �h��
	
	portion,	// ��
	food,		// �H�ו�
	etc,		// ���̑�

	_enum_end,
};

std::string _getHaveItemTypeName(haveItemType item_type);