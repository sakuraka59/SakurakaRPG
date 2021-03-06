#pragma once
#include "UiBase.h"
#include <unordered_map>

using namespace std;

class CharaPlayer;
class CraftUiBase;

class CraftUi : public UiBase {

private: CharaPlayer* _player_obj;
private: CraftUiBase* _list_ui_obj;

private: bool _draw_flag = false;		// 描画しているかどうか
public: CraftUi();

// 初期化
public: void Init(CharaPlayer* player_obj);

// 開く
public: void openUi();

// 閉じる
public: void closeUi();

// 更新処理
public: void Update();



};