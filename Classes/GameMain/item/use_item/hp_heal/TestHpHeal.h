#pragma once
#include "../UseItem.h"


class TestHpHeal : public UseItem {

public: TestHpHeal(CharaBase* chara_obj);
public: bool useSkill() override;
};