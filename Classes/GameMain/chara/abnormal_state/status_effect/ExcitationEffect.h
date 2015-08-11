#pragma once
#include "StatusEffectBase.h"

class CharaBase;

class ExcitationEffect : public StatusEffectBase {

public: ExcitationEffect(CharaBase* chara_obj);
protected: void stateEffectDetail(int effect_num) override;

};