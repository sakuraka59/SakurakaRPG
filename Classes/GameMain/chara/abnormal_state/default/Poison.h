#pragma once
#include "../StateAuto.h"

class CharaBase;

class Poison : public StateAuto{
public: Poison(std::unique_ptr<CharaBase>& chara_obj);
protected: void stateEffect() override;
};