#pragma once
#include "WeaponSheathBase.h"

class TestSheath : public WeaponSheathBase {

public: TestSheath(CharaBase* chara_obj);
protected: void setStateInit() override;

};