#include "CraftRecipeDetail.h"

CraftRecipeDetail::CraftRecipeDetail(string item_id_1, string item_id_2, string item_id_3, string item_id_4,
	string create_item_id, int create_item_num) {

	this->_item_id_1 = item_id_1;
	this->_item_id_2 = item_id_2;
	this->_item_id_3 = item_id_3;
	this->_item_id_4 = item_id_4;

	this->_create_item_id = create_item_id;
	this->_create_item_num = create_item_num;
}

string CraftRecipeDetail::getItemId1() {
	return this->_item_id_1;
}

string CraftRecipeDetail::getItemId2() {
	return this->_item_id_2;
}
string CraftRecipeDetail::getItemId3() {
	return this->_item_id_3;
}
string CraftRecipeDetail::getItemId4() {
	return this->_item_id_4;
}
int CraftRecipeDetail::operator+ (CraftRecipeDetail* craft_recipe_obj){
	return 1;
}

/*
bool CraftRecipeDetail::operator<(const CraftRecipeDetail &rhs) const {
	return true;
}
*/