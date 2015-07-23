#pragma once
#pragma execution_character_set("utf-8")

#include <unordered_map>
#include "ItemBase.h"
#include "../chara/mainStateType.h"

#include "equip_item\EquipItem.h"
/*
#include "use_item/UseItem.h"
#include "equip_item/EquipItem.h"
*/
using namespace std;

enum class itemBaseType {
	_no_type = 0,
	equip,		// 装備
	use,		// 消費
	_enum_end,
};
enum class itemCategoryType {
	_no_type = 0,
	// equip -----------
	weapon,		// 武器
	clothes,	// 服

	// use -------------
	heal,		// 回復薬
	food,		// 食べ物
	_enum_end,
};
enum class itemDetailType {
	_no_type = 0,
	// weapon ----------
	// one hand
	sword,		// 片手剣
	rapier,		// 細剣
	saber,		// 片手曲剣

	// sub
	sheath,		// 鞘

	// two hand


	// clothes ---------
	// main
	hat,		// 帽子、髪飾り
	top,		// トップ（シャツやブラウス系、鎧上）
	bottom,		// ボトム（ズボン、スカート、鎧下）
	outer,		// 上着（パーカーやジャケット、マント）
	socks,		// くつした
	shoes,		// 靴

	bula,		// ブラ、インナー系キャミソール
	pants,		// パンツ

	// sub
	earrings,	// イヤリング
	bracelet,	// 腕輪、篭手
	ring,		// 指輪
	necklace,	// 首飾り
	anklet,		// 足首飾り

	// use -------------
	heal,		// 回復薬
	food,		// 食べ物
	_enum_end,
};

// 読み込み保持用アイテムクラス
class ItemLoadOnlyMaterial {

public: string _item_name = "";
public: itemDetailType _item_type = itemDetailType::_no_type;
		// 装備アイテム用ステータス
public: unordered_map<mainStateType, int> _default_state;			// 基本ステータス
public: unordered_map<abnormalStateType, int> _state_default_list;	// 状態異常用ステータス

		// 消費アイテム用ステータス

		// データセット
public: void setEquipStateData(mainStateType state_type, int state_num) {
	this->_default_state[state_type] = state_num;
}
};

class ItemMasterList {

// 各アイテムのパスリスト
private: static unordered_map<itemDetailType, string> _path_list;

// アイテム名から参照用
private: static unordered_map<string, ItemLoadOnlyMaterial*> _item_master_list;

// レア度、アイテム名から参照
private: static unordered_map<int, unordered_map<string, ItemLoadOnlyMaterial*>> _item_master_rate_list;

// アイテム種類、アイテム名から
private: static unordered_map<itemBaseType, unordered_map<string, ItemLoadOnlyMaterial*>> _item_master_type_list;

// アイテム詳細種類、アイテム名から
private: static unordered_map<itemDetailType, unordered_map<string, ItemLoadOnlyMaterial*>> _item_master_detail_list;

// 読み込み済み判定
private: static bool _load_flag;

private: static itemDetailType _load_item_type;

private: static unordered_map<int, mainStateType> _load_state_list;

private: ItemMasterList();

// ファイル検索をして、全てのアイテムのオブジェクトを作成する
public: static void loadItemList();
// 読み込み基本関数
private: static void loadBase();	
// アイテムの種類ごとに動作振り分け
private: static void loadTypeAndPath(itemDetailType item_type, string dir_path, string item_name);
// 以下ファイル読み込み詳細
// 片手剣
private: static void loadTypeNormalEquip(itemDetailType item_type, string dir_path, string item_name);

// データ読み込み
private: static ifstream loadItemData(string dir_path, string item_name);

// 各種オブジェクトを返す
public: static ItemBase* getItemObjToMaster(string item_name);

private: static ItemBase* ItemMaterialToItemBase(ItemLoadOnlyMaterial* load_item);
};
