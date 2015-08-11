#pragma once
#include "../StateAuto.h"

class CharaBase;

class FeelHot : public StateAuto {
public: FeelHot(CharaBase* chara_obj);
protected: void stateEffect() override;
protected: void EveryFrameEffect() override;
};