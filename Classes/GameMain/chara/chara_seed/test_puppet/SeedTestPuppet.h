#pragma once

#include "../SeedBase.h"

class SeedTestPuppet : public SeedBase {

public: SeedTestPuppet();
protected: void setStateList(std::unique_ptr<CharaBase>& chara_obj) override;

};