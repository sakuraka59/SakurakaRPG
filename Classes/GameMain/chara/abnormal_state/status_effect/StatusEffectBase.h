#pragma once
#include "../StateAuto.h"

class CharaBase;

class StatusEffectBase : public StateAuto {

public: StatusEffectBase(CharaBase* chara_obj);
protected: void stateEffect() override;
protected: virtual void stateEffectDetail(int effect_num);
};