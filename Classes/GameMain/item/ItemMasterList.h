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
	potion,		// 薬
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
	potion,		// 薬
	food,		// 食べ物
	etc,		// その他素材等のアイテム
	_enum_end,
};

// 読み込み保持用アイテムクラス
class ItemLoadOnlyMaterial {

public: string _item_name = "";
public: string _item_id = "";
public: itemDetailType _item_type = itemDetailType::_no_type;
// 共通データ -------------------------------------------------------
// 基本ステータス。装備アイテムなら装備補正、消費アイテムならステータス回復用。
public: unordered_map<mainStateType, int> _default_state;			
public: unordered_map<abnormalStateType, int> _state_default_list;	// 状態異常用ステータス

// 装備アイテム用ステータス -----------------------------------------
// 特にないよ

// 消費アイテム用ステータス -----------------------------------------
public: int _effect_frame = -1;
// アイテム使用による一定時間ステータス補正用
public: unordered_map<mainStateType, int> _correct_state;

// データセット
public: void setStateData(mainStateType state_type, int state_num) {
	this->_default_state[state_type] = state_num;
}

// 消費アイテム補正用データセット
public: bool setCorrectStateData(mainStateType state_type, int state_num) {
	if (this->_item_type < itemDetailType::potion ||
		this->_item_type >= itemDetailType::_enum_end) {

		return false;
	}
	this->_correct_state[state_type] = state_num;
	return true;
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

// ステータス読み込み順番
private: static unordered_map<int, mainStateType> _load_equip_state_list;	// 装備
private: static unordered_map<int, mainStateType> _load_use_state_list;		// 消耗品

private: ItemMasterList();

// ファイル検索をして、全てのアイテムのオブジェクトを作成する
public: static void loadItemList();
// 読み込み基本関数
private: static void loadBase();	
// アイテムの種類ごとに動作振り分け
private: static void loadTypeAndPath(itemDetailType item_type, string dir_path, string item_name);
//-------------------------------------------------------------------
// 以下ファイル読み込み詳細
//-------------------------------------------------------------------
// 片手剣、細剣
private: static void loadTypeNormalEquip(itemDetailType item_type, string dir_path, string item_name);

// 薬
private: static void loadTypeUse(itemDetailType item_type, string dir_path, string item_name);

// データ読み込み
private: static ifstream loadItemData(string dir_path, string item_name);

// 各種オブジェクトを返す
public: static ItemBase* getItemObjToMaster(string item_name);

private: static ItemBase* ItemMaterialToItemBase(ItemLoadOnlyMaterial* load_item);
};
