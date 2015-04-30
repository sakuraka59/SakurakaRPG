#pragma once
#include "StateBase.h"
class CharaBase;
class StateAuto : public StateBase {

public: StateAuto(CharaBase* chara_obj);
protected: void stateUpdate() override;
};