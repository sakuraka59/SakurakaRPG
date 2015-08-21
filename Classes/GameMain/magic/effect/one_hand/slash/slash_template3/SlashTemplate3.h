#pragma once
#include "../../../EffectBase.h"

class SlashTemplate3 : public EffectBase {

private: double _effect_base_x = 0;
private: double _effect_base_y = 0;
private: double _anime_time = 20;
private: double _anime_range = 0;
public: SlashTemplate3(CharaBase* chara_obj,int attack_range, int attack_speed);

public: void magicInitExtend() override;
protected: void UpdateDetail() override;
};