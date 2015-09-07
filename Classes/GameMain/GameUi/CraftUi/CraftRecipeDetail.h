#pragma once
#include <string>
//-------------------------------------------------------------------
//	アイテム作成用レシピオブジェクト
//-------------------------------------------------------------------


using namespace std;

class CraftRecipeDetail {
private: string _item_id_1 = "";
private: string _item_id_2 = "";
private: string _item_id_3 = "";
private: string _item_id_4 = "";

private: string _create_item_id = "";

private: int _create_item_num = 1;

public: CraftRecipeDetail(string item_id_1, string item_id_2, string item_id_3, string item_id_4, string create_item_id, int create_item_num);

public: string operator== (CraftRecipeDetail* craft_recipe_obj);
public: int operator+ (CraftRecipeDetail* craft_recipe_obj);

public: bool operator<(const CraftRecipeDetail &rhs) const {
	return true;
}

		/*
public: int CraftRecipeDetail::operator+ () const {
	return 2;
}
public: bool operator==(const CraftRecipeDetail &obj) const {
	return true;
}
		/*
public: bool operator== (CraftRecipeDetail &craft_recipe_obj){
	string check_recipe_item_id1 = craft_recipe_obj.getItemId1();
	string check_recipe_item_id2 = craft_recipe_obj.getItemId2();
	string check_recipe_item_id3 = craft_recipe_obj.getItemId3();
	string check_recipe_item_id4 = craft_recipe_obj.getItemId4();

	int hoge = 0;

	if (this->_item_id_1 != check_recipe_item_id1 ||
		this->_item_id_2 != check_recipe_item_id2 ||
		this->_item_id_3 != check_recipe_item_id3 ||
		this->_item_id_4 != check_recipe_item_id4){

		hoge = 1;
		return false;
	}
	hoge = 2;
	return true;
}

public: bool operator<(const CraftRecipeDetail& rmaniac) const {
	int hoge = 0;
	if (*this < rmaniac) {
		hoge = 1;
		return true;
	}
	hoge = 2;
	return false;
}
*/
public: string getItemId1();
public: string getItemId2();
public: string getItemId3();
public: string getItemId4();

//public: bool operator<(const CraftRecipeDetail& rmaniac) const;
};


class testClass {
public:
	testClass(int dummy);
	bool operator<(const testClass rhs) const;
};