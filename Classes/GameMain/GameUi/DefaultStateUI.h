#pragma once
#include "UiBase.h"

class DefaultStateGauge;
class CCGauge;
//class DefaultStateNum;
class CharaPlayer;

class DefaultStateUI : public UiBase {

private: DefaultStateGauge* _state_hp_obj;
private: DefaultStateGauge* _state_sp_obj;
private: CCGauge* _state_cc_obj;

//private: DefaultStateNum* _state_num_obj;
public: DefaultStateUI(CharaPlayer* player_obj);

public: void Update();
};