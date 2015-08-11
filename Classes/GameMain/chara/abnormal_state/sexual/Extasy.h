#pragma once
#include "../StateAuto.h"

class CharaBase;

class Extasy : public StateAuto {
public: Extasy(CharaBase* chara_obj);
protected: void stateEffect() override;
protected: void endStateEffect() override;
};