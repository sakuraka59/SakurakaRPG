#pragma once
#include "cocos2d.h"
#include "UiBase.h"

#include "../chara/abnormal_state/abnormalStateType.h"

class CharaPlayer;
class StateBase;
class AbnormalStateView;

using namespace std;
using namespace cocos2d;

class AbnormalStateUI : public UiBase {
private: const bool _DEBUG_FLAG = true;
private: const int _FONT_SIZE = 15;
private: const int _BOTTOM_MARGIN = 3;

private: CharaPlayer* _player_obj;
private: map<abnormalStateType, StateBase*> _state_list;

private: unordered_map<StateBase*, AbnormalStateView*> _state_view_list;

private: unordered_map<StateBase*, cocos2d::LabelTTF*> _state_name_label_list;
private: unordered_map<StateBase*, cocos2d::LabelTTF*> _debug_time_label_list;

public: AbnormalStateUI();
// ‰Šú€”õ
public: void setInit(CharaPlayer* player_obj);

// •`‰æ€”õ‚âXV
private: void setDrawList();
public: void Update();
};