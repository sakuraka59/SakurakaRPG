#pragma once
#include "../StateAuto.h"

class CharaBase;

class Oestrus : public StateAuto {
public: Oestrus(CharaBase* chara_obj);
protected: void stateEffect() override;
protected: void EveryFrameEffect() override;
protected: void endStateEffect() override;
};