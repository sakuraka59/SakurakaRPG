#pragma once
#include "UiBase.h"

class DefaultStateGauge;
class DefaultStateNum;
class CharaPlayer;

class DefaultStateUI : public UiBase {

private: DefaultStateGauge* _state_hp_obj;
private: DefaultStateGauge* _state_sp_obj;

private: DefaultStateNum* _state_num_obj;
public: DefaultStateUI(CharaPlayer* player_obj);

public: void Update();
};