#pragma once

#include "../SeedBase.h"

class SeedTestPuppet : public SeedBase {

public: SeedTestPuppet();
protected: void setStateList(CharaBase* chara_obj) override;

};