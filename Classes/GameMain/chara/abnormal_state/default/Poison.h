#pragma once
#include "../StateAuto.h"

class CharaBase;

class Poison : public StateAuto{

public: Poison(CharaBase* chara_obj);
protected: void stateEffect() override;
};