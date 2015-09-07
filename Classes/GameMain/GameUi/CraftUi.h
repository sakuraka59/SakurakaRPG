#pragma once
#include "UiBase.h"
#include <unordered_map>

using namespace std;

class CharaPlayer;
class CraftUiBase;

class CraftUi : public UiBase {

private: CharaPlayer* _player_obj;
private: CraftUiBase* _list_ui_obj;

private: bool _draw_flag = false;		// •`‰æ‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
public: CraftUi();

// ‰Šú‰»
public: void Init(CharaPlayer* player_obj);

// ŠJ‚­
public: void openUi();

// •Â‚¶‚é
public: void closeUi();

// XVˆ—
public: void Update();



};