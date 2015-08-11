#pragma once
#pragma execution_character_set("utf-8")

//#include "../chara/CharaBase.h"
#include "../chara/mainStateType.h"
#include <unordered_map>       // ハッシュテーブル
#include "haveItemType.h"

class CharaBase;

using namespace std;
class ItemBase {
protected: haveItemType _have_item_type = haveItemType::_no_type;
//	protected Dictionary<mainStateType, int> _add_state = new Dictionary<mainStateType, int>();
public: unordered_map<mainStateType, int> _add_state;
protected: int _weight;	// one item to weight
protected: CharaBase* _chara_obj;
protected: string _item_name = "no name";
protected: string _icon_file_name = "";
//*/
// function
public: ItemBase();
public: virtual bool useItem();
public: void setItemName(string item_name);
public: string getItemName();
public: haveItemType getHaveItemType();
public: void setHaveItemType(haveItemType item_type);
public: void setCharaObj(CharaBase* chara_obj);
};
