#pragma once
#include <map>
#include <unordered_map>
#include "cocos2d.h"
#include "../../../RenderObject.h"

class CharaPlayer;
class ItemBase;
class UseItem;

enum class haveItemType;

using namespace cocos2d;
using namespace std;

class CraftUiBase : public RenderObject {
// 表示に関する設定 -------------------------------------------------
protected: const int _TEXT_LINE_HEIGHT = 30;
protected: const int _FONT_SIZE = 18;
protected: const int _CURSOR_DELAY_TIME = 10;
protected: const int _BG_WIDTH = 200;
protected: const int _LINE_WIDTH = 5;
protected: const string _FONT_FILE = "fonts/APJapanesefontT.ttf";		// 使用フォントファイル（あんず文字等幅
private: const string _NO_SETTING_TEXT = "なし";

// アイテム作成に関する設定 -----------------------------------------
// アイテム最大セット数
protected: const int _ITEM_SET_MAX = 4;
// 使用可能アイテム種類
protected: unordered_map<haveItemType, haveItemType> _use_item_type_list;

private: const int _SET_LABEL_MARGIN = 10;
// CharaPlayer情報 --------------------------------------------------
private: CharaPlayer* _player_obj;
//private: ControllSetting* _controll_setting;

// 操作、表示状況 ---------------------------------------------------
//	0 : アイテム種類一覧	1 : アイテム詳細一覧
private: int _controll_type = 0;

// カーソル操作時におけるディレイ時間カウント
private: int _cursor_delay = 0;


// アイテムタイプ一覧 -------------------------------------------------
private: RenderObject* _type_bg_render_obj;		// 背景描画
private: RenderObject* _type_label_obj;				// 種類文字
private: int _type_num = 0;							// 表示リスト数
private: int _type_cursor = 0;						// カーソル位置
private: unordered_map<int, haveItemType> _type_list;	// カーソル位置からの種類リスト

// アイテム詳細一覧 -------------------------------------------------
private: RenderObject* _detail_bg_render_obj;							// 背景描画
private: unordered_map<haveItemType, RenderObject*> _detail_label_list;	// スキル一覧文字リスト
private: unordered_map<haveItemType, int> _detail_num_list;				// 表示リスト数
private: int _detail_cursor = 0;										// カーソル位置
private: RenderObject* _detail_label_obj;								// 表示するスキル一覧文字
private: haveItemType _open_detail_type;									// 開いて表示しているスキル一覧のスキルタイプ

// アイテム素材設定一覧 -------------------------------------------------
private: RenderObject* _stuff_bg_render_obj;				// 背景描画
private: RenderObject* _stuff_label_obj;					// 種類文字
private: unordered_map<int, LabelTTF*> _stuff_label_list;	// 文字は書き換えが発生するので、一覧で持っておく
private: int _stuff_set_num = 0;							// 表示リスト数
private: map<int, string> _set_item_stuff_list;			// 作成時のアイテム材料セットリスト
private: map<string, int> _set_item_count;				// 同一アイテムをいくつ入れたか

// アイテムオブジェクトリスト
private: unordered_map<haveItemType, unordered_map<int, ItemBase*>> _detail_list;



public: CraftUiBase(CharaPlayer* chara_obj);

// UIの背景を作成して返す
private: RenderObject* getBgRenderObj();

// 素材用UIの背景を作成して返す
private: RenderObject* getStuffBgRenderObj();
// UIの表示系関数 ---------------------------------------------------
// UIを開く
public: void openUi();
// UIを閉じる
public: void closeUi();

// 詳細一覧を開く
public: void openDetailList();
// 詳細一覧を閉じる
public: void closeDetailList();

// 初期化処理系 -----------------------------------------------------

// 種類一覧のラベル初期化
private: void initTypeLabelList();

// タイプごとの一覧ラベルの初期化
private: bool initDetailLabelList(haveItemType item_type);

// タイプごとの一覧ラベルの初期化(消費アイテム系）
private: bool initDetailLabelListToUse(haveItemType item_type);

// 詳細一覧開いた際の初期化処理
private: void initOpenDetailList(haveItemType item_type);


// 更新処理系 -------------------------------------------------------

// 更新処理メイン
public: void Update();
// 種類一覧更新処理
private: void updateListType();
// 詳細一覧更新処理
private: void updateListDetail();
		 

// 作成作成準備 - アイテム選択 --------------------------------------
private: bool setItemMaterial(UseItem* item_obj);

// 最後にセットしたアイテムをはずす
private: bool unsetItemMaterial();

// アイテムセット時、作成可能レシピを取得
private: bool checkItemRecipe();
// その他 -----------------------------------------------------------
private: string getTypeName(haveItemType item_type);
// リストの表示幅を返す
public: int getDrawWidth();

// ラベル用オブジェクトを作成して返す
private: LabelTTF* getLabelTTF(string set_string_data);


};