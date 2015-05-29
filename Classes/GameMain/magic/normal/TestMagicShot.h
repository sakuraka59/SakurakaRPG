#pragma once
#include "../MagicBase.h"

class TestMagicShot : public MagicBase {
public: TestMagicShot(CharaBase* chara_obj, int draw_x, int draw_y, int draw_z, double angle);

public: void magicInit() override;
protected: void UpdateDetail() override;
};
