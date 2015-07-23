#pragma once
#include "WeaponSheathBase.h"

class TestSheath : public WeaponSheathBase {

public: TestSheath();
protected: void setStateInit() override;

};