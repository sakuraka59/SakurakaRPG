#pragma once
#include "StatusEffectBase.h"

class CharaBase;

class HoneyEffect : public StatusEffectBase {

public: HoneyEffect(CharaBase* chara_obj);
protected: void stateEffectDetail(int effect_num) override;

};