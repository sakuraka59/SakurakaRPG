#pragma once

#include "../SeedBase.h"

class CharaBase;

class SeedTestPuppet : public SeedBase {

public: SeedTestPuppet(CharaBase* chara_obj);
protected: void setStateList(CharaBase* chara_obj) override;
};