#pragma once
#include "../../EffectBase.h"

class SlashUp1 : public EffectBase {
public: SlashUp1(CharaBase* chara_obj);

public: void magicInitExtend() override;
protected: void UpdateDetail() override;
};