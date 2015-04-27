#ifndef __ITEM_BASE__
#define __ITEM_BASE__

#include "../chara/CharaBase.h"
//#include "../chara/mainStateType.h"
#include <unordered_map>       // ハッシュテーブル

class ItemBase
{
	
//	protected Dictionary<mainStateType, int> _add_state = new Dictionary<mainStateType, int>();
public: std::unordered_map<mainStateType, int> _add_state;
protected: int _weight;	// one item to weight
protected: CharaBase* _chara_obj;
protected: std::string _item_name = "no name";
//*/
// function
public: ItemBase(CharaBase* chara_obj);
public: virtual bool useItem();
public: std::string getItemName();
};
// */
#endif