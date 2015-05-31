#pragma once
#include "../MagicBase.h"

class TestMagicShot : public MagicBase {
public: TestMagicShot(CharaBase* chara_obj);

public: void magicInitExtend() override;
protected: void UpdateDetail() override;
};
