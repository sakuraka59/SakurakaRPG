#pragma once
#include "../WeaponBase.h"

class WeaponSheathBase : public WeaponBase
{
public: WeaponSheathBase();
protected: bool checkExtendEquipItem() override;

// ���������ɂ�鑕�������`�F�b�N
public: bool checkEquipRelease() override;
};