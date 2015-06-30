#pragma once
#include "../SeedBase.h"
class SeedHuman : public SeedBase {

public: SeedHuman(CharaBase* chara_obj);
//public: void Update() override;
public: void updateAngleDetail() override;
};