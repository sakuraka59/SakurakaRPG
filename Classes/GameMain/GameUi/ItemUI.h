#pragma once
#include "UiBase.h"

class CharaPlayer;
class ObjItemList;

class ItemUi : public UiBase {
private: bool _draw_flag = false;
private: double _draw_alpha = 0;
private: CharaPlayer* _player_obj;

private: ObjItemList* _player_item_list_obj;

public: ItemUi(CharaPlayer* player_obj);

public: void closeItemUi();		// 閉じる
public: void openItemUi();		// 自身のアイテムUIのみ開く
public: void openItemUiToObj();	// オブジェクトからのアイテム取得時に使う




};