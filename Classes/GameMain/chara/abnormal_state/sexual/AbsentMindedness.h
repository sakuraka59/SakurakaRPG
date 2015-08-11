#pragma once
#include "../StateAuto.h"

class CharaBase;

class AbsentMindedness : public StateAuto {
public: AbsentMindedness(CharaBase* chara_obj);
protected: void stateEffect() override;
};