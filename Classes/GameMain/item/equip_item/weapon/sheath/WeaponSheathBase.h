#pragma once
#include "../WeaponBase.h"

class WeaponSheathBase : public WeaponBase
{
public: WeaponSheathBase();
protected: bool checkExtendEquipItem() override;

// 他装備時による装備解除チェック
public: bool checkEquipRelease() override;
};